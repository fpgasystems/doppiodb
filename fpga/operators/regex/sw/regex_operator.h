#ifndef REGEX_OPERATOR
#define REGEX_OPERATOR

//TODO this is all defined in fregex as well
/*#define MAX_CHARS 128
#define MAX_STATES 32

	#ifndef DEBUG
	#define DEBUG false
	#endif

#define bool short
#define byte unsigned char*/

#include "../../hwoperators.h"
#include "./regex-util/fregex.h"


struct REGEX_AFU_CONFIG {
   // CL #1
   union {
      uint64_t          qword0[8];       // make it a whole cacheline
      struct {
         void         * basePtr;        
         void         * vbasePtr;          
         void         * retPtr;         
         uint32_t       batcount    : 32;        
         uint32_t       tailWidth   : 32;         
      };
   };

   // CL#2
   union {
      uint64_t          qword1[8];       // make it a whole cacheline
      struct {
         uint8_t        config[64];
      };
   };
};


#endif 
