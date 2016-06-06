


#include "../include/platform.h"

using namespace AAL;

#define  ASEAFU

///////////////////////////////////////////////////////////////////////////////
///
///  MyRuntimeClient Implementation
///
///////////////////////////////////////////////////////////////////////////////
RuntimeClient::RuntimeClient() :
    m_Runtime(),        // Instantiate the AAL Runtime
    m_pRuntime(NULL),
    m_isOK(false)
{
   NamedValueSet configArgs;
   NamedValueSet configRecord;

   // Publish our interface
   SetSubClassInterface(iidRuntimeClient, dynamic_cast<IRuntimeClient *>(this));

   m_Sem.Create(0, 1);

   // Using Hardware Services requires the Remote Resource Manager Broker Service
   // Note that this could also be accomplished by setting the environment variable
   // XLRUNTIME_CONFIG_BROKER_SERVICE to librrmbroker
#if defined( HWAFU )
   configRecord.Add(XLRUNTIME_CONFIG_BROKER_SERVICE, "librrmbroker");
   configArgs.Add(XLRUNTIME_CONFIG_RECORD,configRecord);
#endif

   if(!m_Runtime.start(this, configArgs)){
      m_isOK = false;
      return;
   }
   m_Sem.Wait();
}
///////////////////////////////////////////////////////////////////////////////
RuntimeClient::~RuntimeClient()
{
    m_Sem.Destroy();
}
///////////////////////////////////////////////////////////////////////////////
btBool RuntimeClient::isOK()
{
   return m_isOK;
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeStarted(IRuntime *pRuntime,
                                   const NamedValueSet &rConfigParms)
{
   // Save a copy of our runtime interface instance.
   m_pRuntime = pRuntime;
   m_isOK = true;
   m_Sem.Post(1);
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::end()
{
   m_Runtime.stop();
   m_Sem.Wait();
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeStopped(IRuntime *pRuntime)
{
   MSG("Runtime stopped");
   m_isOK = false;
   m_Sem.Post(1);
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeStartFailed(const IEvent &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("Runtime start failed");
   ERR(pExEvent->Description());
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeAllocateServiceFailed( IEvent const &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("Runtime AllocateService failed");
   ERR(pExEvent->Description());
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeAllocateServiceSucceeded(IBase *pClient,
                                                    TransactionID const &rTranID)
{
   MSG("Runtime Allocate Service Succeeded");
}
///////////////////////////////////////////////////////////////////////////////
void RuntimeClient::runtimeEvent(const IEvent &rEvent)
{
   MSG("Generic message handler (runtime)");
}
///////////////////////////////////////////////////////////////////////////////
IRuntime * RuntimeClient::getRuntime()
{
   return m_pRuntime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HWService::~HWService()
{
  
  m_Sem.Destroy();
}

void HWService::OnTransactionStarted( TransactionID const &TranID,
                                   btVirtAddr           AFUDSMVirt,
                                   btWSSize             AFUDSMSize)
{
  MSG("Transaction Started");
  m_AFUDSMVirt = AFUDSMVirt;
  m_AFUDSMSize = AFUDSMSize;
  //
  m_Sem.Post(1);
}
///////////////////////////////////////////////////////////////////////////////
void HWService::OnTransactionFailed( const IEvent &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("Runtime AllocateService failed");
   ERR(pExEvent->Description());
   m_bIsOK = false;
   ++m_Result;
   m_AFUDSMVirt = NULL;
   m_AFUDSMSize =  0;
   ERR("Transaction Failed");
   m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnTransactionComplete
void HWService::OnTransactionComplete( TransactionID const &TranID)
{
   m_AFUDSMVirt = NULL;
   m_AFUDSMSize =  0;
   MSG("Transaction Complete");
   m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnTransactionStopped
void HWService::OnTransactionStopped( TransactionID const &TranID)
{
   m_AFUDSMVirt = NULL;
   m_AFUDSMSize =  0;
   MSG("Transaction Stopped");
   m_Sem.Post(1);
}
void HWService::serviceEvent(const IEvent &rEvent)
{
   ERR("unexpected event 0x" << hex << rEvent.SubClassID());
}

void HWService::OnContextWorkspaceSet( TransactionID const &TranID)
{
   MSG("Context Set");
   m_Sem.Post(1);
}

void HWService::OnWorkspaceFreed(TransactionID const &TranID)
{
   MSG("OnWorkspaceFreed");
   // Freed so now Release() the Service through the Services IAALService::Release() method
   (dynamic_ptr<IAALService>(iidService, m_pAALService))->Release(TransactionID());
}

void HWService::OnWorkspaceFreeFailed(const IEvent &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("OnWorkspaceAllocateFailed");
   ERR(pExEvent->Description());
   ++m_Result;
   m_Sem.Post(1);
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
    Hardware service setup method
*/
void HWService::allocHWService(){

  //
  NamedValueSet Manifest;
  NamedValueSet ConfigRecord;

  #if defined( HWAFU )                /* Use HWService hardware */
    ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME, "libHWSPLAFU");
    ConfigRecord.Add(keyRegAFU_ID,"00000000-0000-0000-0000-000011100181");
    ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_AIA_NAME, "libAASUAIA");

  #elif defined ( ASEAFU )
    ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME, "libASESPLAFU");
    ConfigRecord.Add(AAL_FACTORY_CREATE_SOFTWARE_SERVICE,true);

  #else
    ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME, "libSWSimSPLAFU");
    ConfigRecord.Add(AAL_FACTORY_CREATE_SOFTWARE_SERVICE,true);
  #endif

  Manifest.Add(AAL_FACTORY_CREATE_CONFIGRECORD_INCLUDED, ConfigRecord);
  Manifest.Add(AAL_FACTORY_CREATE_SERVICENAME, "HW Service");
  MSG("Allocating Service");

  // Allocate the Service and allocate the required workspace.
  //   Note that here you allocate the workspaces first processed by this service
  //   If it consumed workspaces created by others, then you pass them through the service
  //   constructor when you first created it.
  m_runtimeClient->getRuntime()->allocService(dynamic_cast<IBase *>(this), Manifest);

  m_Sem.Wait();
}
// <begin IServiceClient interface>
void HWService::serviceAllocated(IBase *pServiceBase,
                                     TransactionID const &rTranID)
{
   m_pAALService = pServiceBase;
   ASSERT(NULL != m_pAALService);

   // Documentation says SPLAFU Service publishes ISPLAFU as subclass interface
   m_SPLService = subclass_ptr<ISPLAFU>(pServiceBase);

   ASSERT(NULL != m_SPLService);
   if ( NULL == m_SPLService ) return;

   MSG("Service Allocated");

   m_Sem.Post(1);
}

void HWService::serviceAllocateFailed(const IEvent &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("Failed to allocate a Service");
   ERR(pExEvent->Description());
   ++m_Result;
   m_Sem.Post(1);
}

void HWService::serviceFreed(TransactionID const &rTranID)
{
   MSG("Service Freed");
   // Unblock Main()
   m_Sem.Post(1);
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
    Allocate HW service workspace memory
*/
bool HWService::allocate_workspace(unsigned int size){
  //
  MSG("Allocate Workspace.... ");
  
  m_SPLService->WorkspaceAllocate(size, TransactionID());
  
  m_Sem.Wait();

  return true;
}

void HWService::OnWorkspaceAllocated(TransactionID const &TranID,
                                          btVirtAddr           WkspcVirt,
                                          btPhysAddr           WkspcPhys,
                                          btWSSize             WkspcSize)
{
   AutoLock(this);
   m_AFUCTXVirt = WkspcVirt;
   m_AFUCTXPhys = WkspcPhys;
   m_AFUCTXSize = WkspcSize;
   MSG("Got Workspace size: "<<WkspcSize);         // Got workspace so unblock the Run() thread
   m_Sem.Post(1);
}

void HWService::OnWorkspaceAllocateFailed(const IEvent &rEvent)
{
   IExceptionTransactionEvent * pExEvent = dynamic_ptr<IExceptionTransactionEvent>(iidExTranEvent, rEvent);
   ERR("OnWorkspaceAllocateFailed");
   ERR(pExEvent->Description());
   ++m_Result;
   m_Sem.Post(1);
}