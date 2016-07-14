
#ifndef __cplusplus
#include "fpga.h"
#endif
#include "fpga.hpp"




// Copyright (c) 2007-2015, Intel Corporation
//
// Redistribution  and  use  in source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of  source code  must retain the  above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name  of Intel Corporation  nor the names of its contributors
//   may be used to  endorse or promote  products derived  from this  software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
// IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT  SHALL THE COPYRIGHT OWNER  OR CONTRIBUTORS BE
// LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
// CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED  TO,  PROCUREMENT  OF
// SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE,  DATA, OR PROFITS;  OR BUSINESS
// INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY  OF LIABILITY,  WHETHER IN
// CONTRACT,  STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE  OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//****************************************************************************
/// @file HelloSPLLB.cpp
/// @brief Basic SPL AFU interaction.
/// @ingroup HelloSPLLB
/// @verbatim
/// Intel(R) QuickAssist Technology Accelerator Abstraction Layer Sample Application
///
///    This application is for example purposes only.
///    It is not intended to represent a model for developing commercially-deployable applications.
///    It is designed to show working examples of the AAL programming model and APIs.
///
/// AUTHORS: Joseph Grecco, Intel Corporation.
///
/// This Sample demonstrates the following:
///    - The basic structure of an AAL program using the AAL Runtime APIs.
///    - The ISPLAFU and ISPLClient interfaces of the SPLAFU Service.
///    - System initialization and shutdown.
///    - Use of interface IDs (iids).
///    - Accessing object interfaces through the Interface functions.
///
/// This sample is designed to be used with the SPLAFU Service.
///
/// HISTORY:
/// WHEN:          WHO:     WHAT:
/// 06/15/2015     JG       Initial version started based on older sample code.@endverbatim
//****************************************************************************
//#define  ASEAFU
#define HWAFU

//TODO maybe call this from BBPinit
extern "C" {
void fpga_init() {
  
  MSG(" Start FPGA Init"); 
  pthread_mutex_lock(&fpga_mutex);
  MSG("acquired mutex");
  if(my_fpga == NULL) 
  {
    MSG("fpga object null");
    my_fpga = new FPGA();
    MSG("fpga object initial allocation, start thread to fill it");
    getFPGA(my_fpga);
  }
  pthread_mutex_unlock(&fpga_mutex);
}

void* FPGAmalloc(size_t size)
{
   //return malloc(size);
  if(my_fpga == NULL) 
  {
      MSG("FPGAmalloc: NULL");
    fpga_init();
  }
  return my_fpga->malloc(size, &size);
}

void* FPGAmallocmax(size_t size, size_t *maxsize, int emergency)
{
   if(my_fpga == NULL) 
   {
      MSG("FPGAmallocmax: NULL");
      fpga_init();
   }
   return my_fpga->malloc(size, maxsize);
}

void* FPGAreallocmax(void* ptr, size_t size, size_t *psize, int emergency)
{
   //TODO On shrink do not change pointer!!
   void* newaddr = FPGAmallocmax(size, psize, emergency);
   if (newaddr)
   {
      memcpy(newaddr, ptr, size);
      return newaddr;
   }
   MSG("FPGA REALLOC: FAIL");
   return NULL;
}

void FPGAfree(void *blk)
{
   my_fpga->free(blk);
}

void FPGAregex(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               void* retBase,
               char regex)
{
  
  //MSG("Processing on FPGA..."<<pthread_self());
  /*printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);*/

  auto start_time = std::chrono::high_resolution_clock::now();

  Fthread t( fthread_regex(my_fpga, reinterpret_cast<btVirtAddr>(base), 
  	                    reinterpret_cast<btVirtAddr>(vbase), 
  						reinterpret_cast<btVirtAddr>(retBase), count, width, regex) );
  t.join();

  //regex.printStatusLine();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()) / 1000.0;
  
  double Throughput  = (double(count*64) / double(MB(1))) / (execTime/1000.0); 
  double opLocalTime = t.timing();
  
  printf("Items: %d,  Time[ms] %.10f, TP[MB/s] %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);
   //MSG("Processing on FPGA done."<<pthread_self());*/

   return;
}

void FPGAparallelRegex(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               void* retBase,
               char regex)
{
  
   //MSG("Parallel Processing on FPGA..."<<pthread_self());
  /*printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);*/

   Fthread ts[4];

   auto start_time = std::chrono::high_resolution_clock::now();

   //Start 4 threads
   //TODO split horizontially
   //split count into 4
   unsigned int partCount = (count / 4);
   unsigned int lastCount = (count - 3*partCount);
   unsigned char* curBase = reinterpret_cast<btVirtAddr>(base);
   unsigned char* curRetBase = reinterpret_cast<btVirtAddr>(retBase);
   for (int i = 0; i < 3; i++)
   {
      ts[i] = Fthread(  fthread_regex(my_fpga, curBase, 
  	                     reinterpret_cast<btVirtAddr>(vbase), 
  						      curRetBase, partCount, width, regex) );
      curBase += (partCount*width);
      curRetBase += (partCount*sizeof(uint16_t));
   }
   //Create last thread
   ts[3] = Fthread(  fthread_regex(my_fpga, curBase, 
  	                     reinterpret_cast<btVirtAddr>(vbase), 
  						      curRetBase, lastCount, width, regex) );


   //Try to join 4 threads
   for (int i = 0; i < 4; i++)
   {
      ts[i].join();
   }

 
   //MSG("Parallel execution done.");

   auto end_time = std::chrono::high_resolution_clock::now();
   double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()) / 1000.0;
  
   double Throughput  = (double(count*64) / double(MB(1))) / (execTime/1000.0); 
   double opLocalTime = 0;//t.timing();
  
   /*printf("Items: %d,  Time[ms] %.10f, TP[MB/s] %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);*/
   //MSG("Processing on FPGA done."<<pthread_self());

   return;
}


} //extern C
