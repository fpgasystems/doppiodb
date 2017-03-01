
#include "../../hwoperators.h"

struct TESTCOUNT_AFU_CONFIG {
   // CL #1
   union {
      uint64_t          qword0[8];       // make it a whole cacheline
      struct {
         void         * pSource;         /// 63:0
         void         * pDest;           /// 127:64
         uint32_t       num_cls;         //  191:128
         uint32_t       test_type;
         uint32_t       test_value;
         uint32_t       tuples_count;
      };
   };
   // CL#2
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename T>
FthreadRec * fthread_testCount(FPGA * my_fpga, short int* src, unsigned int long count, 
                              const char * test, short int threshold){
  

  //----------------------------- Operator specific configuration -------------------------------//
  TESTCOUNT_AFU_CONFIG * afu_cfg = (struct TESTCOUNT_AFU_CONFIG*)(my_fpga->malloc( sizeof(TESTCOUNT_AFU_CONFIG) ));

  afu_cfg->pSource      = reinterpret_cast<unsigned char*>(src);
  afu_cfg->pDest        = my_fpga->malloc(sizeof(int));
  afu_cfg->num_cls      = ((count*sizeof(short int) + 63) / 64);
  afu_cfg->tuples_count = count;

  printf("testcount op: src: %p, dst: %p, cls: %d\n", src, afu_cfg->pDest, afu_cfg->num_cls);

  printf("count = %d\n", count); fflush(stdout);
  
  afu_cfg->test_value  = threshold;
  afu_cfg->test_type   = 0xFFFFFFFF;

  if( strcmp(test, "=") == 0 )        afu_cfg->test_type = 0;
  else if( strcmp(test, "!=") == 0 )  afu_cfg->test_type = 1;
  else if( strcmp(test, "<") == 0 )   afu_cfg->test_type = 2;
  else if( strcmp(test, "<=") == 0 )  afu_cfg->test_type = 3;
  else if( strcmp(test, ">") == 0 )   afu_cfg->test_type = 4;
  else if( strcmp(test, ">=") == 0 )  afu_cfg->test_type = 5;
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return  my_fpga->create_fthread(TEST_AND_COUNT_OP, 
                                  reinterpret_cast<unsigned char*>(afu_cfg), 
                                  sizeof(TESTCOUNT_AFU_CONFIG), afu_cfg->pDest );
 }

uint32_t fthread_testCount(){ return TEST_AND_COUNT_OP; }
