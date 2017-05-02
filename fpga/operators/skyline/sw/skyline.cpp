/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 */

#include "../../hwoperators.h"

struct SKYLINE_AFU_CONFIG {
   // CL #1
   union {
      uint64_t          qword0[8];       // make it a whole cacheline
      struct {
         void         * dim[8];
      };
   };
   // CL#2
   union {
      uint64_t          qword1[8];       // make it a whole cacheline
      struct {
         void         * skyline[8];
      };
   };
   // CL#3
   union {
      uint32_t          qword2[16];       // make it a whole cacheline
      struct {
         uint32_t       tupleCount;
         uint32_t       dimensionMask;
         uint32_t       dimensionCount;
         uint32_t       dimensionComparisons;
      };
   };
};


FthreadRec * fthread_skyline(FPGA * my_fpga, int* dim[], int* skyline[], uint64_t count, uint32_t numDims)
{
  

  //----------------------------- Operator specific configuration -------------------------------//
  SKYLINE_AFU_CONFIG * afu_cfg = (struct SKYLINE_AFU_CONFIG*)(my_fpga->malloc( sizeof(SKYLINE_AFU_CONFIG) ));

//  afu_cfg->dim[0]     = dim[numDims];
//  afu_cfg->skyline[0] = skyline[numDims];

  int opCode = SKYLINE128_OP;

  int mask = 0x0000007F;

  switch(numDims)
  {
    case 7: mask = 0x0000007F; break;
    case 6: mask = 0x0000003F; break;
    case 5: mask = 0x0000001F; break;
    case 4: mask = 0x0000000F; break;
    case 3: mask = 0x00000007; break;
    case 2: mask = 0x00000003; break;
  }

  for(int i = 0; i < numDims+1; i++)
  {
    afu_cfg->dim[i]     = dim[i];
    afu_cfg->skyline[i] = skyline[i];
  }
  afu_cfg->tupleCount           = uint32_t(count);
  afu_cfg->dimensionMask        = mask;
  afu_cfg->dimensionCount       = numDims;
  afu_cfg->dimensionComparisons = 0;

  //Thread allocation
  return  my_fpga->create_fthread(opCode, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(SKYLINE_AFU_CONFIG) );
 }

uint32_t fthread_skyline(){ return SKYLINE256_OP; }


struct SKYLINE_AFU_CONFIG2 {
   // CL#1
   union {
      uint64_t          qword1[8];       // make it a whole cacheline
      struct {
         void         * skylineBase;
         void         * requeueBase;
         uint32_t       tupleCount           : 32;
         uint32_t       dimensionCount       : 32;
         uint32_t       dimensionComparisons : 32;
      };
   };
   // CL #2,3                                                                                                   
   union {                                                                                                    
     uint64_t          qword0[16];       // make it a whole cacheline                                         
     struct {                                                                                                
       void         * dim[16];                                                                               
     };                                                                                                      
   };  
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FthreadRec * fthread_skyline(FPGA * my_fpga, void* dim[], int* tmpDims, int* skylines, 
                             uint64_t count, uint32_t numDims)
{
  

  //----------------------------- Operator specific configuration -------------------------------//
  SKYLINE_AFU_CONFIG2 * afu_cfg = (struct SKYLINE_AFU_CONFIG2*)(my_fpga->malloc( sizeof(SKYLINE_AFU_CONFIG2) ));

  int opCode = SKYLINE128_OP;

  for(int i = 0; i < numDims; i++)
  {
    afu_cfg->dim[i]     = dim[i];
  }

  afu_cfg->skylineBase          = skylines;
  afu_cfg->requeueBase          = tmpDims;
  afu_cfg->tupleCount           = uint32_t(count);
  afu_cfg->dimensionCount       = numDims;
  afu_cfg->dimensionComparisons = 0;

  
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return  my_fpga->create_fthread(opCode, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(SKYLINE_AFU_CONFIG2) );
 }


