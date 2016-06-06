#ifndef FILE_FPGAH_INCLUDED
#define FILE_FPGAH_INCLUDED

//#include "include/fpgaapi.h"
//#define FPGAzalloc FPGAmalloc

#ifdef __cplusplus
    extern "C" {
#endif

	//extern int fp_scan_offset;
	//extern int fp_scan_length;
	extern void* fp_base_address;
	extern void* fp_curr_address;
   extern size_t fp_workspace_size;

	//extern int* tbl_nlen;
	//extern char** tbl_name;
	//extern int* tbl_offs;
	//extern int* tbl_len;

	extern void* runtimeClient;
	extern void* theApp;

   extern void* FPGAmalloc(size_t);
   extern void* FPGAmallocmax(size_t, size_t*, int);
   extern void* FPGAreallocmax(void*, size_t, size_t*, int);
   extern void FPGAfree(void*);

   extern void FPGAregex(void*, void*, unsigned int, unsigned int, void*);

   //TODO make not extern
	extern void* fpga_init();
	/*extern void fpga_free();

	extern int fpga_process(char* name, int nlen);

	extern int fpga_set_offset(int offs);
	extern int fpga_set_length(int len);
	extern int fpga_set_tablename(char* name, int nlen);*/

#ifdef __cplusplus
    }
#endif


#endif /* !FILE_FPGA_INCLUDED */
