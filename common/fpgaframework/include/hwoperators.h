
#ifndef __HWOPERATORS_H__
#define __HWOPERATORS_H__

#include <string.h>
#include "fpgaapi.h" 
/*
   hw operator template

   fthread_name(ServiceHW * my_fpga, args...){
	
	// Set up IO data structures
	// Set up AFU parameters data struct

	enqueue command

	return handle
   }


*/

//////////////////////////////////////////////////////////////////////////////////////////
enum OPCODE {
  REGEX_OP                  = 1,
  MURMUR_OP                 = 2,
  TEST_AND_COUNT_OP         = 3,
  MIN_MAX_SUM_OP            = 4,
  COPY_32_OP                = 5,
  COPY_64_OP                = 6,
  COPY_128_OP               = 7,
  COPY_256_OP               = 8,
  COPY_512_OP               = 9
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
fpga::Thread * fthread_copy(FPGA * my_fpga, FQueue<T> * src, FQueue<T> * dst){
    
  int sz = sizeof(T);
  unsigned int opcode = (sz == 32)?  COPY_32_OP  : 
                        (sz == 64)?  COPY_64_OP  : 
                        (sz == 128)? COPY_128_OP : 
                        (sz == 256)? COPY_256_OP : COPY_512_OP; 
  //---------------------------------- Thread allocation ----------------------------------------//
  fpga::Thread * t_thread = new fpga::Thread(my_fpga, opcode);
 	
  //----------------------------- Operator specific configuration -------------------------------//
 	t_thread->config_params = reinterpret_cast<struct AFU_CONFIG*> (
                            setupAFU_CONFIG(my_fpga, 
 		                                        reinterpret_cast<btVirtAddr>(src),
                                            reinterpret_cast<btVirtAddr>(dst))
                            );
    
  //------------------------------ enqueue the thread on the FPGA queue -------------------------//
 	my_fpga->enqueue_command(t_thread);

 	return t_thread;
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fpga::Thread * fthread_regex(FPGA * my_fpga, btVirtAddr src, btVirtAddr vsrc, 
                             btVirtAddr dst, unsigned int long batcount, int tailwidth){
    
  //---------------------------------- Thread allocation ----------------------------------------//
  fpga::Thread * t_thread = new fpga::Thread(my_fpga, REGEX_OP);
  
  //----------------------------- Operator specific configuration -------------------------------//
  // construct thread config parameters
  t_thread->config_params = reinterpret_cast<struct AFU_CONFIG*> ( setupAFU_CONFIG(my_fpga, src, dst, batcount) );
  
  MSG("AFU vsrc =" << std::hex << (void *)vsrc);

  t_thread->config_params->param1 = vsrc;

  t_thread->config_params->param2 = tailwidth;
  //
  uint8_t cfgBytes[64] = {83, 116, 114, 97, 115, 115, 101, 126, 126, 126, 126, 126, 126, 126, 126, 126, 0, 126, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  
  for (int i = 0; i < 64; i++) 
  {
    t_thread->config_params->config[i] = cfgBytes[i];
  }
  
  //------------------------------ enqueue the thread on the FPGA queue -------------------------//
  my_fpga->enqueue_command(t_thread);

  return t_thread;
}

#endif // __HWOPERATORS_H__