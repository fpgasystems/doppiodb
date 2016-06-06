
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
fpga::Thread * fthread_copy(FPGA * my_fpga, FQueue<T> * src, FQueue<T> * dst){
    
  char name[256] = "";
  sprintf(name, "copy%d", (int)((sizeof(T) << 3)>>4 ) );
  //---------------------------------- Thread allocation ----------------------------------------//
  fpga::Thread * t_thread = new fpga::Thread(my_fpga, name);
 	
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
                             btVirtAddr dst, unsigned int long batcount, int tailwidth, int id){
    
  char name[256] = "";
  sprintf(name, "regex%d", id );

  //---------------------------------- Thread allocation ----------------------------------------//
  fpga::Thread * t_thread = new fpga::Thread(my_fpga, name);
  
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

  //char *elem = "VARDATA(PG_GETARG_VARCHAR_P(1));   ";
  //uint16_t cpsize = 35;
  

  //int endp = 64;
  //int scnt = 0;
  //uint16_t* sdata = (uint16_t*) src;


  //for (int x = 0; x < batcount; x++) 
 // {
  //  sdata[x]= x*64; 
  //}
  
  
  //------------------------------ enqueue the thread on the FPGA queue -------------------------//
  my_fpga->enqueue_command(t_thread);

  return t_thread;
}

fpga::Thread * fthread_regex2(FPGA * my_fpga, btVirtAddr src, btVirtAddr dst, unsigned int long numStr, int id){
    
  char name[256] = "";
  sprintf(name, "regex%d", id );

  //---------------------------------- Thread allocation ----------------------------------------//
  fpga::Thread * t_thread = new fpga::Thread(my_fpga, name);
  
  //----------------------------- Operator specific configuration -------------------------------//
  // construct thread config parameters
  t_thread->config_params = reinterpret_cast<struct AFU_CONFIG*> ( setupAFU_CONFIG(my_fpga, src, dst, numStr) );
    //
  uint8_t cfgBytes[64] = {83, 116, 114, 97, 115, 115, 101, 126, 126, 126, 126, 126, 126, 126, 126, 126, 0, 126, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      
    
      for (int i=0; i<64; i++) {
        src[i] = cfgBytes[i];
      }

      
   
      char *elem = "VARDATA(PG_GETARG_VARCHAR_P(1));   ";
      uint16_t cpsize = 35;

      int probSize = 1024;

      int endp = 64;
      int scnt = 0;

      for (int x = 0; x<numStr; x++) {

        

        uint8_t* sdata = (uint8_t*) src;

        sdata[endp]= cpsize;

        memcpy(sdata + endp+2, elem, cpsize);  

        sdata[endp + 2 + cpsize] = 0;
     
        uint16_t pos = (endp)/64 +1;

        sdata[4*1024*1024 - 64*(1+scnt/32) + ((scnt)%32)*2 ] = pos % 256;
        sdata[4*1024*1024 - 64*(1+scnt/32) + ((scnt)%32)*2 +1 ] = (pos / 256);

        endp += 64;
        scnt++;   
      }
  
  
  //------------------------------ enqueue the thread on the FPGA queue -------------------------//
  my_fpga->enqueue_command(t_thread);

  return t_thread;
}

#endif // __HWOPERATORS_H__