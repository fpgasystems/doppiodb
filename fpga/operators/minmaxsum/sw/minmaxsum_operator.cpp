#include "../../hwoperators.h"

struct MINMAXSUM_AFU_CONFIG {
   // CL #1
   union {
      uint64_t     qword0[8];         // make it a whole cacheline
      struct {
        int*      pSource;           // 0:63
        int*      pDestination;      // 64:127
        uint32_t  numberOfCachelines;
      };
   };
   // CL#2
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename T>
FthreadRec * fthread_minmaxsum(FPGA* my_fpga, int* source, int* destination, int countTuples)
{ 
  //----------------------------- Operator specific configuration -------------------------------//
  MINMAXSUM_AFU_CONFIG* afu_cfg = (struct MINMAXSUM_AFU_CONFIG*)(my_fpga->malloc( sizeof(MINMAXSUM_AFU_CONFIG) ));

  afu_cfg->pSource = source;
  afu_cfg->pDestination = destination;
  afu_cfg->numberOfCachelines = ((countTuples*sizeof(int) + 63) / 64);
  
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return my_fpga->create_fthread(MIN_MAX_SUM_OP, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(MINMAXSUM_AFU_CONFIG), afu_cfg->pDestination);
}

uint32_t fthread_minmaxsum(){ return MIN_MAX_SUM_OP; }
