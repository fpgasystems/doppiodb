

#include <string.h>

using namespace AAL;

#ifndef __UTILS_H__
#define __UTILS_H__

struct OneCL {                      // Make a cache-line sized structure
  btUnsigned32bitInt dw[16];       //    for array arithmetic
};


struct AFU_CONFIG {
   // CL #1
   union {
      btUnsigned64bitInt          qword0[8];       // make it a whole cacheline
      struct {
         void                   * pSource;         /// 63:0
         void                   * pDest;           /// 127:64
         void                   * param1;          //  191:128
         btUnsigned32bitInt       num_cl;          /// 223:192
         btUnsigned32bitInt       param2;          //  255:224
         btUnsigned32bitInt       param3;
         btUnsigned32bitInt       param4;
         btUnsigned32bitInt       param5;
         btUnsigned32bitInt       param6;
         btUnsigned32bitInt       param7;
         btUnsigned32bitInt       param8;
         btUnsigned32bitInt       param9;
         btUnsigned32bitInt       param10;
      };
   };

   // CL#2
   union {
      btUnsigned64bitInt          qword1[8];       // make it a whole cacheline
      struct {
         uint8_t              config[64];
      };
   };
};

struct int128{
  unsigned int data0, data1, data2, data3;

  int128(){
    data0  = 0;
    data1  = 1;
    data2  = 2;
    data3  = 3;
  }
};

struct int96{
  unsigned int data0, data1, data2;

  int96(){
    data0  = 0;
    data1  = 1;
    data2  = 2;
  }
};

struct int256{
  unsigned int data0, data1, data2, data3, data4, data5, data6, data7;

  int256(){
    data0  = 0;
    data1  = 1;
    data2  = 2;
    data3  = 3;
    data4  = 4;
    data5  = 5;
    data6  = 6;
    data7  = 7;
  }
};

struct int512{
  unsigned int data0, data1, data2, data3, data4, data5, data6, data7;
  unsigned int data10, data11, data12, data13, data14, data15, data16, data17;

  int512(){
    data0  = 0;
    data1  = 1;
    data2  = 2;
    data3  = 3;
    data4  = 4;
    data5  = 5;
    data6  = 6;
    data7  = 7;
    data10  = 10;
    data11  = 11;
    data12  = 12;
    data13  = 13;
    data14  = 14;
    data15  = 15;
    data16  = 16;
    data17  = 17;
  }
};

#endif // __UTILS_H__
void _DumpCL( void * pCL) ;
double get_time();

