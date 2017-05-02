/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 */
#ifndef FILE_FPGAH_INCLUDED
#define FILE_FPGAH_INCLUDED

#include "fpga_udf.h"


#ifdef __cplusplus
    extern "C" {
#endif


   	extern void* FPGAmalloc(size_t);
   	extern void* FPGAmallocmax(size_t, size_t*, int);
   	extern void* FPGAreallocmax(void*, size_t, size_t*, int);
   	extern void  FPGAfree(void*);

   	//TODO make not extern
	extern void fpga_init();


#ifdef __cplusplus
    }
#endif


#endif /* !FILE_FPGA_INCLUDED */
