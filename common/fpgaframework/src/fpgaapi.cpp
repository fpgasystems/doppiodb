

#include <string.h>

#include "../include/fpgaapi.h"

//#define  HWAFU
#define  ASEAFU

//****************************************************************************
// UN-COMMENT appropriate #define in order to enable either Hardware or ASE.
//    DEFAULT is to use Software Simulation.
//****************************************************************************

using namespace AAL;
/**/

FPGA::FPGA(){
  
  ///////////////////////////////////////////////////////////
  srvAllocated = false;
  opCount      = 0;
  numOfSuppOps = 0;

  for(int i = 0; i < MAX_NUM_ALLOWED_OPS; i++)
    srvOperators[i] = false;
}
///////////////////////////////////////////////////////////////////////////////
FPGA::~FPGA()
{
  
  delete srvHndle;
  
  delete m_manager;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool FPGA::release(){

  // SPL Related 
  MSG("Stopping SPL Transaction");
  srvHndle->m_SPLService->StopTransactionContext(TransactionID());
  srvHndle->m_Sem.Wait();
  MSG("SPL Transaction complete");

  srvHndle->m_SPLService->WorkspaceFree(m_manager->get_virt_base(), TransactionID());
  srvHndle->m_Sem.Wait();
  MSG("End Runtime Client");
  srvHndle->m_runtimeClient->end();
  MSG("Release Succeeded");
  
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
    Allocate HW service workspace memory
*/
bool FPGA::initiate(){
  
  MSG("Starting SPL Transaction with Workspace");
  srvHndle->m_SPLService->StartTransactionContext(TransactionID(), 
                                                  m_manager->get_virt_base(), 
                                                  100);
  srvHndle->m_Sem.Wait();

  if(srvHndle->m_AFUDSMSize == 0) return false;
  return true;
}
 
///////////////////////////////////////////////////////////////////////////////////////////
/* 
  This function should work like this:
   1- Read the currently configured operators on the FPGA and add them to the list
   2- Read the library of bitstreams and add them to the list

   FOR NOW, it just has a fixed set of operators written directly in the list
*/
void FPGA::obtainSupportedOperators(){

  // 
  supportedOperators[0] = "regex1";
  supportedOperators[1] = "regex2";
  supportedOperators[2] = "regex3";
  supportedOperators[3] = "regex4";
  supportedOperators[4] = "copy64";
  supportedOperators[5] = "copy128";
  supportedOperators[6] = "copy256";

  supportedOperators[7] = "murmur";
  supportedOperators[8] = "test_and_count";
  supportedOperators[9] = "min_max_sum";
  supportedOperators[10] = "copy32";

  numOfSuppOps          = 11;

}
///////////////////////////////////////////////////////////////////////////////////////////
void setupQueue(FPGA * my_fpga){

  my_fpga->cmd_queue  = reinterpret_cast<FQueue<struct OneCL>*>( my_fpga->m_manager->get_virt_base() );
  ::memset(my_fpga->cmd_queue, 0, sizeof(FQueue<struct OneCL>));
      
  my_fpga->cmd_queue->m_buffer          = reinterpret_cast<struct OneCL*>( my_fpga->m_manager->get_virt_base()     + 
                                                                  sizeof(FQueue<struct OneCL>));
  my_fpga->cmd_queue->m_capacity        = CMD_QUEUE_SIZE;
  my_fpga->cmd_queue->m_capacity_bytes  = CMD_QUEUE_SIZE * sizeof(struct OneCL);
  my_fpga->cmd_queue->update_bytes_rate = 2048;
  my_fpga->cmd_queue->m_producer_idx    = 0;
  my_fpga->cmd_queue->m_producer_bytes  = 0;
  my_fpga->cmd_queue->m_producer_done   = false;
  my_fpga->cmd_queue->m_consumer_idx    = 0;
  my_fpga->cmd_queue->m_consumer_bytes  = 0;

  my_fpga->cmd_queue->m_producer_code  = FQUEUE_VALID_CODE;
  my_fpga->cmd_queue->m_crb_code       = FQUEUE_VALID_CODE;

}
/* 
  
*/
void FPGA::setUpCommandQueue(){

  // 
  std::thread setCMQ(setupQueue, this);

  setCMQ.join();

  MSG("cmd_queue = "<< cmd_queue->m_producer_bytes << ", " << cmd_queue->m_producer_done);

  // Make sure that this memory is set

}
//********************************************************************************************************//
//********************************************************************************************************//
//********************************************************************************************************//
//********************************************************************************************************//
//********************************************************************************************************//
//********************************************************************************************************//
void * FPGA::malloc(unsigned int size_in_bytes){
  
  void * ptr = NULL;
  if(m_manager != NULL)
  {
    mem_alloc_mutex.lock();
    ptr = m_manager->malloc(size_in_bytes);
    mem_alloc_mutex.unlock();
  } 
  return ptr;
} 

///////////////////////////////////////////////////////////////////////////////////////////
void FPGA::free(void * ptr){

  if(m_manager != NULL) 
  {
    mem_alloc_mutex.lock();
    m_manager->free(ptr);
    mem_alloc_mutex.unlock();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////
void FPGA::enqueue_command(fpga::Thread * t_thread){
  //
  struct OneCL cmd_CL;
  
  cmd_queue_mutex.lock();

  ::memset(&cmd_CL, 0, sizeof(struct OneCL));

  // construct code word:
  unsigned int code = (t_thread->accID  & 0x0000FFFF) | 
                      (((t_thread->uID + OP_STATUS_DSM_OFFSET) << 16) & 0x00FF0000) | 
                                                      0x01000000  | 
                                                      0x80000000;

  cmd_CL.dw[0] = (btUnsigned32bitInt)(code);
  cmd_CL.dw[1] = (btUnsigned32bitInt)(AAL::bt64bitCSR(t_thread->config_params));
  cmd_CL.dw[2] = (btUnsigned32bitInt)(AAL::bt64bitCSR(t_thread->config_params) >> 32);
  
  while( !cmd_queue->push(cmd_CL) );

  cmd_queue_mutex.unlock();
}

//-------------------------------------------------------------------------//
void FPGA::enqueue_command(unsigned int code){
  //
  struct OneCL cmd_CL;
  
  cmd_queue_mutex.lock();

  ::memset(&cmd_CL, 0, sizeof(struct OneCL));

  cmd_CL.dw[0] = (btUnsigned32bitInt)(code);
  
  while( !cmd_queue->push(cmd_CL) );

  cmd_queue_mutex.unlock();
}
//-------------------------------------------------------------------------//
int FPGA::allocateOp(){
  
  int idx = -1;

  op_alloc_mutex.lock();

  if(opCount == MAX_NUM_ALLOWED_OPS)
  {
    for(int i = 0; i < MAX_NUM_ALLOWED_OPS; i++)
      if( !srvOperators[i] ) 
      {
        srvOperators[i] = true;
        idx = i;
        break;
      }    
  }
  else 
  {
    int id = opCount; 
    srvOperators[id] = true;
    opCount += 1;
    idx = id;
  }

  op_alloc_mutex.unlock();

  return idx;
}

//-------------------------------------------------------------------------//
int FPGA::locateOpAcc(std::string fname){

  // search in the supported opcodes
  for(int i = 0; i < numOfSuppOps; i++) 
    if(supportedOperators[i].compare(fname) == 0 ) return i + 1;

  return -1;
}
//-------------------------------------------------------------------------//

HWOperator * FPGA::create_hwop(std::string opName){
  
  // allocate operator
  HWOperator * hwop = new HWOperator;

  hwop->AccLocation   = locateOpAcc(opName);
  hwop->UniqueID      = allocateOp();

  return hwop;
}
//-------------------------------------------------------------------------//
void FPGA::terminate(){
  
  MSG("enqueue terminate command\n");
  unsigned int code = (DSM_RESET_CMD & 0x0000FFFF) | 0xfb000000;
  enqueue_command(code);

  MSG("\n cmd_queue producer_bytes = "<< (cmd_queue->m_producer_bytes) <<", cmd_queue consumer_bytes = "<< (cmd_queue->m_consumer_bytes));
  
  SleepMilli(10);
  release();
  MSG("\n FPGA Process Terminated\n");
}

///////////////////////////////////////////////////////////////////////////////////////////

FPGA * getFPGA(){
  
  MSG("Get Hardware Service Handle....");

  FPGA * my_fpga = new FPGA();

  // create the interface to AAL Platform
  RuntimeClient *  runtimeClient = new RuntimeClient;
  
  my_fpga->srvHndle = new HWService(runtimeClient);

  my_fpga->srvHndle->allocHWService();
  my_fpga->srvHndle->allocate_workspace(APP_WORKSPACE_MAXIMUM_SIZE);

  my_fpga->m_manager = new MemoryManagerClient(my_fpga->srvHndle->m_AFUCTXVirt, 
                                               my_fpga->srvHndle->m_AFUCTXPhys, 
                                               my_fpga->srvHndle->m_AFUCTXSize);

  MSG("Setup Command Queue");
  my_fpga->setUpCommandQueue();

  MSG("Initiate Transaction");
  if( ! my_fpga->initiate() ) return NULL;
  
  MSG("Get Supported Ops");
  my_fpga->obtainSupportedOperators();

  MSG("Hardware Service Handle Obtained Successfully!");
  
  return my_fpga;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FPGA Thread Class Implementation                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace fpga;

Thread::Thread(FPGA * t_fpga, char t_name[])
{
  //

  HWOperator * hwop = t_fpga->create_hwop( std::string(t_name) );

  name                = new std::string(t_name);
  parent_fpga         = t_fpga;
  accID               = hwop->AccLocation;
  uID                 = hwop->UniqueID;
  parent_process_ID   = -1;
  config_params       = NULL;
  status_line         = reinterpret_cast<struct OneCL*>(
                          t_fpga->srvHndle->m_AFUDSMVirt + (hwop->UniqueID + OP_STATUS_DSM_OFFSET)*CL(1)
                          );

  ::memset(status_line, 0, 64);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
Thread::Thread(Thread * t_thread){
  //
  name                = new std::string(*(t_thread->name));
  parent_fpga         = t_thread->parent_fpga;
  accID               = t_thread->accID;
  uID                 = t_thread->uID;
  parent_process_ID   = t_thread->parent_process_ID;
  config_params       = t_thread->config_params;
  status_line         = t_thread->status_line;

  delete t_thread;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Thread::join(){

  unsigned char status = status_line->dw[0];
  // Wait for SPL VAFU to finish code
  while ( status != OPERATOR_DONE_STATE ) 
  {
    SleepMicro( 1 );
    status = status_line->dw[0];
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Thread::timing(){
  
  unsigned int cycles = status_line->dw[3];
  return (cycles*5.0/1000000.0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Thread::printStatusLine(){
  
  parent_fpga->std_out_mutex.lock();

  _DumpCL(status_line);

  parent_fpga->std_out_mutex.unlock();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace AAL;

btVirtAddr setupAFU_CONFIG(FPGA * srvHndle, btVirtAddr src, btVirtAddr dst, unsigned int param1, unsigned int param2){

  btVirtAddr param_ptr = (btVirtAddr)(srvHndle->malloc( sizeof(AFU_CONFIG) ));

  AFU_CONFIG * cparam    = reinterpret_cast<AFU_CONFIG *>(param_ptr);
  
  // Initialize the command buffer
  ::memset(cparam, 0, sizeof(AFU_CONFIG));
  cparam->param2  = param1;
  cparam->param3  = param2;
  cparam->pSource = src;
  cparam->pDest   = dst;

  MSG("AFU Context=" << std::hex << (void *)cparam <<
      " Src="        << std::hex << (void *)cparam->pSource <<
      " Dest="       << std::hex << (void *)cparam->pDest << std::dec);

  return param_ptr;
}

btVirtAddr setupAFU_CONFIG(FPGA * srvHndle, btVirtAddr src, btVirtAddr dst, unsigned long int numLines){

  btVirtAddr param_ptr = (btVirtAddr)(srvHndle->malloc( sizeof(AFU_CONFIG) ));

  AFU_CONFIG * cparam    = reinterpret_cast<AFU_CONFIG *>(param_ptr);
  
  // Initialize the command buffer
  ::memset(cparam, 0, sizeof(AFU_CONFIG));
  cparam->pSource = src;
  cparam->pDest   = dst;
  cparam->num_cl  = numLines;

  MSG("AFU Context=" << std::hex << (void *)cparam <<
      " Src="        << std::hex << (void *)cparam->pSource <<
      " Dest="       << std::hex << (void *)cparam->pDest << std::dec);


  return param_ptr;
}

