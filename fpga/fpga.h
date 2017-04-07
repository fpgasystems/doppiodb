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
