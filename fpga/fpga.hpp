#ifndef FILE_FPGA_HPP_INCLUDED
#define FILE_FPGA_HPP_INCLUDED


#include "operators/hwoperators.h"
#include "fpga_udf.h"

static FPGA * my_fpga;
static pthread_mutex_t fpga_mutex;
static int* use_sw;

void GenerateData(int Dimensions,char Distribution,int Count,int* dims[]);

struct datapoint {
  struct datapoint *next;
  uint64_t timestamp;
  uint32_t dimensions[7]; 
};

#define FALSE 0
#define TRUE 1
#define BOOL uint32_t
#endif /* !FILE_FPGA_INCLUDED */
