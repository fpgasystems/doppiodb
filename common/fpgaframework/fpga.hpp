#ifndef FILE_FPGA_HPP_INCLUDED
#define FILE_FPGA_HPP_INCLUDED

#include <aalsdk/AAL.h>
#include <aalsdk/xlRuntime.h>
#include <aalsdk/AALLoggerExtern.h> // Logger

#include <aalsdk/service/ISPLAFU.h>       // Service Interface
#include <aalsdk/service/ISPLClient.h>    // Service Client Interface
#include <aalsdk/kernel/vafu2defs.h>      // AFU structure definitions (brings in spl2defs.h)

#include <string.h>

#include "include/fpgaapi.h"
#include "include/hwoperators.h"

using namespace AAL;

static FPGA * my_fpga;
static pthread_mutex_t fpga_mutex;
int    id;

struct REGEX_CNTXT {
   union {
      btUnsigned64bitInt          qword0[8];       // make it a whole cacheline
      struct {
         union {                                   // first qword
            btUnsigned64bitInt    dword0;
            struct {
               btUnsigned64bitInt rsvd0:   32;
               btUnsigned64bitInt delay:   16;     // undefined, but in the structure definition, set to 0
            };
         };
         void          *pSource;                   ///< Source user-mode virtual address, cache-line aligned.
         void          *pDest;                     ///< Destination user-mode virtual address, cache-line aligned.
         btUnsigned32bitInt      num_bat;
         btUnsigned32bitInt      tail_width;
         void*         pBase;
         void*         pVBase;
         //btUnsigned32bitInt      num_bat;
         //btUnsigned32bitInt      tail_width;

      };
   };
   //cache line for config
   uint8_t              config[64];

   union {
         btUnsigned64bitInt          qword1[8];       // make it a whole cacheline
         struct {
            btUnsigned32bitInt       Status;          ///< Bit0 true if done
            //#define  VAFU2_CNTXT_STATUS_DONE   0x00000001      ///< Bit0 selector
         };
      };
   }; // struct REGEX_CNTXT

#endif /* !FILE_FPGA_INCLUDED */
