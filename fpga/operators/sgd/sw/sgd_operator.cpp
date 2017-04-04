#include "../../hwoperators.h"

struct SGD_AFU_CONFIG {
  // CL #1
  union {
    uint64_t    qword0[8];         // make it a whole cacheline
    struct {
      float*    source_address;
      int32_t*  destination_address;
      uint32_t  mini_batch_size;
      float     step_size;
      uint32_t  number_of_epochs;
      uint32_t  dimension;
      uint32_t  number_of_samples;
      uint32_t  number_of_CL_to_process;
      uint32_t  binarize_b_value;
      uint32_t  b_value_to_binarize_to;
    };
  };
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename T>
FthreadRec * fthread_sgd_row(FPGA* my_fpga, float* ab, uint32_t numberOfIterations, uint32_t numFeatures, uint32_t numSamples, float stepSize, int32_t* x_history) {

  SGD_AFU_CONFIG* afu_cfg = (struct SGD_AFU_CONFIG*)( my_fpga->malloc(sizeof(SGD_AFU_CONFIG)) );

  uint64_t ab_address = (uint64_t)ab;
  uint64_t x_history_address = (uint64_t)x_history;
  printf("ab_address: %x %x\n", (ab_address>>32)&0xFFFFFFFF, ab_address&0xFFFFFFFF);
  printf("x_historyi_address: %x %x\n", (x_history_address>>32)&0xFFFFFFFF, x_history_address&0xFFFFFFFF);

  afu_cfg->source_address = ab;
  afu_cfg->destination_address = x_history;
  afu_cfg->mini_batch_size = 36-1;
  afu_cfg->step_size = stepSize;
  afu_cfg->number_of_epochs = numberOfIterations;
  afu_cfg->dimension = numFeatures;
  afu_cfg->number_of_samples = numSamples;

  uint32_t t = (numFeatures+1)/16;
  uint32_t r = (numFeatures+1)%16;
  if (r > 0)
    t++;
  uint32_t numCacheLines = t*numSamples;
  cout << "numCacheLines: " << numCacheLines << endl;
  afu_cfg->number_of_CL_to_process = numCacheLines;

  afu_cfg->binarize_b_value = 0;
  afu_cfg->b_value_to_binarize_to = 0;

  return my_fpga->create_fthread(SGD_OP, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(SGD_AFU_CONFIG), afu_cfg->destination_address);
}