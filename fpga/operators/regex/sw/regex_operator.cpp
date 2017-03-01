
#include "regex_operator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


FthreadRec* fthread_regex(FPGA * t_fpga, unsigned char* src, unsigned char* vsrc, 
                          unsigned char* dst, unsigned int long batcount, int tailwidth, char* regex)
{
  // construct thread config parameters
  printf(" allocate regex config struct\n"); fflush(stdout);
  REGEX_AFU_CONFIG * afu_cfg = (struct REGEX_AFU_CONFIG*)(t_fpga->malloc( sizeof(REGEX_AFU_CONFIG) ));
  
  printf(" allocated, set config params: %p\n", afu_cfg); fflush(stdout);
  afu_cfg->basePtr   = src;
  afu_cfg->vbasePtr  = vsrc;
  afu_cfg->retPtr    = dst;
  afu_cfg->batcount  = batcount;
  afu_cfg->tailWidth = tailwidth;

  //Generate config
  unsigned char configBytes[512];
  int configLen = 0;
  printf("Regex: %s\n", regex);
  fregex_get_config(regex, 8, 16, configBytes, &configLen);
  printf("Config length: %i\n", configLen*8);
  printf("Config: ");
  for (int i = 0; i < 64; i++)
  {
    printf("%c ", configBytes[i]);
  }
  printf("\n");

  //Copy configuration
  memcpy(afu_cfg->config, configBytes, sizeof(uint8_t)*64);
  
  printf("params: %p, %p, %p, %d, %d\n", afu_cfg->basePtr, afu_cfg->vbasePtr, 
           afu_cfg->retPtr, afu_cfg->batcount, afu_cfg->tailWidth); fflush(stdout);

  printf(" parameters set, create fthread\n"); fflush(stdout);
  //enqueue the thread on the FPGA queue
  return t_fpga->create_fthread(REGEX_OP, reinterpret_cast<unsigned char*>(afu_cfg), sizeof(REGEX_AFU_CONFIG) );
}

uint32_t fthread_regex(){ return REGEX_OP; }
