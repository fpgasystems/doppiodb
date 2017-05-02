/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 */

#include "../../hwoperators.h"

struct COPY_AFU_CONFIG {
   // CL #1
   union {
      uint64_t          qword0[8];       // make it a whole cacheline
      struct {
         void         * pSource;         /// 63:0
         void         * pDest;           /// 127:64
         uint32_t       num_cl;          //  191:128
      };
   };
   // CL#2
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FthreadRec * fthread_copy(FPGA * my_fpga, unsigned char * src, unsigned char * dst, uint32_t count){
  

  //----------------------------- Operator specific configuration -------------------------------//
  COPY_AFU_CONFIG * afu_cfg = (struct COPY_AFU_CONFIG*)(my_fpga->malloc( sizeof(COPY_AFU_CONFIG) ));

  afu_cfg->pSource = src;
  afu_cfg->pDest   = dst;
  afu_cfg->num_cl  = (count*4 + 63)/64;
  
  //---------------------------------- Thread allocation ----------------------------------------//
  
  return  my_fpga->create_fthread(COPY_32_OP, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(COPY_AFU_CONFIG) );
 }

uint32_t fthread_copy(){ return COPY_32_OP; }
