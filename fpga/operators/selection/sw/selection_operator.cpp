#include "../../hwoperators.h"

struct SELECTION_AFU_CONFIG {
   // CL #1
   union {
      uint64_t     qword0[8];         // make it a whole cacheline
      struct {
        int*      pPredicateSource;  // 0:63       
        int*      pSource;           // 64:127
        int*      pDestination;      // 128:191
        uint32_t  selectionType;
        uint32_t  lowerThreshold;
        uint32_t  upperThreshold;
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
FthreadRec * fthread_selection(FPGA* my_fpga, int* predicateSource, int* source, int* destination, const char* selectionType, int lowerThreshold, int upperThreshold, int countTuples)
{ 
  //----------------------------- Operator specific configuration -------------------------------//
  SELECTION_AFU_CONFIG* afu_cfg = (struct SELECTION_AFU_CONFIG*)(my_fpga->malloc( sizeof(SELECTION_AFU_CONFIG) ));

  afu_cfg->pPredicateSource = predicateSource;
  afu_cfg->pSource = source;
  afu_cfg->pDestination = destination;
  afu_cfg->numberOfCachelines = ((countTuples*sizeof(int) + 63) / 64);
  
  afu_cfg->lowerThreshold = lowerThreshold;
  afu_cfg->upperThreshold = upperThreshold;
  
  if( strcmp(selectionType, "=") == 0 )        afu_cfg->selectionType = 0;
  else if( strcmp(selectionType, "!=") == 0 )  afu_cfg->selectionType = 1;
  else if( strcmp(selectionType, "<") == 0 )   afu_cfg->selectionType = 2;
  else if( strcmp(selectionType, "<=") == 0 )  afu_cfg->selectionType = 3;
  else if( strcmp(selectionType, ">") == 0 )   afu_cfg->selectionType = 4;
  else if( strcmp(selectionType, ">=") == 0 )  afu_cfg->selectionType = 5;
  else afu_cfg->selectionType = 0;
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return my_fpga->create_fthread(SELECTION_OP, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(SELECTION_AFU_CONFIG), afu_cfg->pDestination);
}

uint32_t fthread_selection(){ return SELECTION_OP; }
