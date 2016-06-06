#ifndef __FPGA_H__
#define __FPGA_H__


#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

#include <string.h>

#include <stdlib.h>
#include <fstream>
#include <math.h>

#include "platform.h"
#include "fqueue.h"
#include "MemoryManager.h"
#include "utils.h"



using namespace AAL;

// Constraints
#define APP_WORKSPACE_MAXIMUM_SIZE       MB(2048)
#define MAX_NUM_ALLOWED_OPS              32
#define MAX_NUM_OF_SUPPORTED_OPS         32

//////////////////////////       DSM Layout        /////////////////////////

// Framework Status Lines
#define AFU_ID_DSM_OFFSET                0      // Reserved by AAL
#define PT_STATUS_DSM_OFFSET             1      
#define CTX_STATUS_DSM_OFFSET            3
#define ALLOC_OPERATORS_DSM_OFFSET       4

// Command Queue
#define CMD_QUEUE_DSM_OFFSET             8

// FThreads Status Lines
#define OP_STATUS_DSM_OFFSET             32

////////////////////////////////////////////////////////////////////////////
#define CMD_QUEUE_SIZE 32
////////////////////////////////////////////////////////////////////////////
#define OPERATOR_DONE_STATE              0x04
#define OPERATOR_IDLE_STATE              0x00

#define CTX_RESET_CMD                    0x00000001
#define DSM_RESET_CMD                    0x00000002

class FPGA;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace fpga{

class Thread{
public:
  Thread(FPGA * fpga, char t_name[]);
  Thread(Thread * t_thread);

  std::string       *   name;
  int                   accID;
  int                   uID;
  int                   parent_process_ID;

  struct AFU_CONFIG *   config_params;
  struct OneCL      *   status_line;

  FPGA              *   parent_fpga;


  //

  bool    join();
  //bool    stop();
  double  timing();
  void    printStatusLine();
};


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HWOperator{

  unsigned int   UniqueID;
  unsigned int   AccLocation;

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class FPGA
{

public:

	FPGA();
    
  ~FPGA();
  
  //-----------------------------------------------------------------//
  //----------------- FPGA Process Init & Release -------------------//
  //-----------------------------------------------------------------//
  bool            initiate();
  bool            release();
  void            setUpCommandQueue();
  void            obtainSupportedOperators();

  //-----------------------------------------------------------------//
  //----------------- FPGA Process Services -------------------------//
  //-----------------------------------------------------------------//
  void            enqueue_command(fpga::Thread * opHndle);
  void            enqueue_command(unsigned int code);
  HWOperator    * create_hwop(std::string opName);
  int             allocateOp();
  int             locateOpAcc(std::string fname);
  void            terminate();
  void          * malloc(unsigned int size_in_bytes);
  void            free(void * ptr);

  //-----------------------------------------------------------------//
  //---------------------- Service member objects -------------------//
  //-----------------------------------------------------------------//
public:
   // Interface to platform dependent layer
   HWService            * srvHndle;

   // Workspace info
   MemoryManagerClient  * m_manager;
   std::mutex             mem_alloc_mutex;

   //
   bool                   srvAllocated;
   unsigned int           opCount;
   bool                   srvOperators[MAX_NUM_ALLOWED_OPS];
   std::mutex             op_alloc_mutex;
   
   int                    numOfSuppOps;
   std::string            supportedOperators[MAX_NUM_OF_SUPPORTED_OPS];

   FQueue<struct OneCL> * cmd_queue;
   std::mutex             cmd_queue_mutex;

   //
   std::mutex             std_out_mutex;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FQueue<T>* setupCRB(FPGA * srvHndle, unsigned int capacity){
  
  btVirtAddr crb_ptr;

  if( srvHndle != 0 )
  {
    crb_ptr   = (btVirtAddr)(srvHndle->malloc( sizeof(FQueue<T>) ));
  }
  else crb_ptr   = (btVirtAddr)(std::malloc( sizeof(FQueue<T>) ));

  if(crb_ptr == NULL) MSG(" malloc failed");

  FQueue<T>* crb       = reinterpret_cast<FQueue<T>*>(crb_ptr);
  
  // Make sure the size is multiples of cache lines and integer number of tuples fit
  unsigned int size_in_bytes    = capacity*sizeof(T);
  unsigned int correct_capacity = capacity;
  if((size_in_bytes % 64) != 0)
  {
    int type_bytes = sizeof(T);
    int pow_2_factor   = ((type_bytes%32) == 0)? 2  :
                         ((type_bytes%16) == 0)? 4  : 
                         ((type_bytes%8)  == 0)? 8  : 
                         ((type_bytes%4)  == 0)? 16 : 
                         ((type_bytes%2)  == 0)? 32 : 64;

    correct_capacity = capacity - (capacity % pow_2_factor) + pow_2_factor;
  }


  if( srvHndle != 0 ) crb->m_buffer        = reinterpret_cast<T*>(srvHndle->malloc(correct_capacity*sizeof(T)));
  else                crb->m_buffer        = reinterpret_cast<T*>(std::malloc(correct_capacity*sizeof(T)));

  

  //crb->m_size = 0;
  crb->m_capacity = correct_capacity;
  crb->m_capacity_bytes = correct_capacity * sizeof(T);
  crb->update_bytes_rate = 2048;
  crb->m_producer_idx = 0;
  crb->m_producer_bytes = 0;
  crb->m_producer_done = false;
  crb->m_consumer_idx = 0;
  crb->m_consumer_bytes = 0;
  crb->m_producer_code  = 0;
  crb->m_crb_code       = FQUEUE_VALID_CODE;
  
  return crb;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
FPGA       * getFPGA();
btVirtAddr   setupAFU_CONFIG(FPGA * srvHndle, btVirtAddr src, btVirtAddr dst, unsigned int param1, unsigned int param2);
btVirtAddr   setupAFU_CONFIG(FPGA * srvHndle, btVirtAddr src, btVirtAddr dst, unsigned long int numLines = 0);

#endif // __FPGA_H__ 
