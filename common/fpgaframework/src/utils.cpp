
#include "../include/platform.h"
#include "../include/fqueue.h"
#include "../include/utils.h"

using namespace AAL;

void _DumpCL( void * pCL) 
 {
    MSG(" " << std::hex << std::setfill('0') << std::uppercase);
    btUnsigned32bitInt *pu32 = reinterpret_cast<btUnsigned32bitInt*>(pCL);
    for( int i = 0; i < ( CL(1) / sizeof(btUnsigned32bitInt)); ++i ) {
       MSG( "0x" << std::setw(8) << *pu32 << " ");
       ++pu32;
    }
    MSG("" << std::nouppercase);
 }  // _DumpCL

 double get_time()
{
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec*1e-6;
}
