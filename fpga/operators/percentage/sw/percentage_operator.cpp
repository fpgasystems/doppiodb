#include "../../hwoperators.h"

struct PERCENTAGE_AFU_CONFIG {
   // CL #1
   union {
      uint64_t          qword0[8];       // make it a whole cacheline
      struct {
        void         * data_src;         /// 63:0
        void         * pred_src;         /// 127:64
        void         * pDest;           /// 191:128

        uint32_t       num_cl;          //  223:192
      };
   };
   // CL#2
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FthreadRec * fthread_percentage(FPGA * my_fpga, unsigned char * d_src, unsigned char * p_src, unsigned char * dst, uint32_t count){
  

  //----------------------------- Operator specific configuration -------------------------------//
  PERCENTAGE_AFU_CONFIG * afu_cfg = (struct PERCENTAGE_AFU_CONFIG*)(my_fpga->malloc( sizeof(PERCENTAGE_AFU_CONFIG) ));

  afu_cfg->data_src = d_src;
  afu_cfg->pred_src = p_src;
  afu_cfg->pDest    = dst;
  afu_cfg->num_cl   = (count*4 + 63) / 64;
  
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return  my_fpga->create_fthread(PERCENTAGE_OP, reinterpret_cast<unsigned char*>(afu_cfg), 
                                  sizeof(PERCENTAGE_AFU_CONFIG));
 }

uint32_t fthread_percentage()
{
  return PERCENTAGE_OP;
}
