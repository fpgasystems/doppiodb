
#ifndef __HWOPERATORS_H__
#define __HWOPERATORS_H__

#include "fpgaapi.h" 

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////      OPERATORS OPCODES       //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

enum OPCODE {
  REGEX_OP                  = 1,
  MURMUR_OP                 = 2,
  TEST_AND_COUNT_OP         = 3,
  MIN_MAX_SUM_OP            = 4,
  COPY_32_OP                = 5,
  COPY_64_OP                = 6,
  COPY_128_OP               = 7,
  COPY_256_OP               = 8,
  COPY_512_OP               = 9,
  PERCENTAGE_OP             = 10,
  MAC_OP                    = 11,
  SELECTION_OP              = 12,
  SKYLINE256_OP             = 13,
  SKYLINE128_OP             = 14,
  SKYLINE64_OP              = 15,
  SGD_OP                    = 16
};

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////     OPERATORS PROTOTYPES     //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
FthreadRec* fthread_copy(FPGA * my_fpga, unsigned char* src, unsigned char* dst, uint32_t count);

uint32_t fthread_copy();

FthreadRec* fthread_regex(FPGA * my_fpga, unsigned char* src, unsigned char* vsrc, 
                          unsigned char* dst, unsigned int long batcount, 
                          int tailwidth, const char * regex);
uint32_t fthread_regex();

//template <typename T>
FthreadRec* fthread_testCount(FPGA * my_fpga, short int* src, unsigned int long count, 
                              const char * test, short int threshold);

uint32_t fthread_testCount();

FthreadRec * fthread_percentage(FPGA * my_fpga, unsigned char * d_src, unsigned char * p_src, 
                                unsigned char * dst, uint32_t count);

uint32_t fthread_percentage();

FthreadRec * fthread_mac(FPGA * my_fpga, unsigned char * src, unsigned char * dst, uint32_t count, 
                        short int mulFactor, int  addFactor);

uint32_t fthread_mac();

FthreadRec* fthread_selection(FPGA* my_fpga, int* predicateSource, int* source, int* destination,  const char* selectionType, int lowerThreshold, int upperThreshold, int countTuples);

uint32_t fthread_selection();

FthreadRec* fthread_minmaxsum(FPGA* my_fpga, int* source, int* destination, int countTuples);

uint32_t fthread_minmaxsum();

FthreadRec * fthread_skyline(FPGA * my_fpga, int* dim[], int* skyline[], uint64_t count, uint32_t numDims);
FthreadRec * fthread_skyline(FPGA * my_fpga, void* dim[], int* tmpDims, int* skylines, uint64_t count, uint32_t numDims);
uint32_t fthread_skyline();

FthreadRec * fthread_sgd_row(FPGA* my_fpga, float* ab, uint32_t numberOfIterations, uint32_t numFeatures, uint32_t numSamples, float stepSize, int32_t* x_history);

#endif // __HWOPERATORS_H__
