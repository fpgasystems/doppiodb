

#include <aalsdk/AAL.h>
#include <aalsdk/xlRuntime.h>
#include <aalsdk/AALLoggerExtern.h> // Logger


#include <aalsdk/service/ISPLAFU.h>       // Service Interface
#include <aalsdk/service/ISPLClient.h>    // Service Client Interface
#include <aalsdk/kernel/vafu2defs.h>      // AFU structure definitions (brings in spl2defs.h)

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <aalsdk/kernel/aaltypes.h>
#include <aalsdk/kernel/spl2defs.h> // SPL2AFU_DSM

BEGIN_NAMESPACE(AAL)

// Convenience macros for printing messages and errors.
#ifdef MSG
# undef MSG
#endif // MSG
#define MSG(x) std::cout << __AAL_SHORT_FILE__ << ':' << __LINE__ << ':' << __AAL_FUNC__ << "() : " << x << std::endl
#ifdef ERR
# undef ERR
#endif // ERR
#define ERR(x) std::cerr << __AAL_SHORT_FILE__ << ':' << __LINE__ << ':' << __AAL_FUNC__ << "() **Error : " << x << std::endl

// Print/don't print the event ID's entered in the event handlers.
#if 1
# define EVENT_CASE(x) case x : MSG(#x);
#else
# define EVENT_CASE(x) case x :
#endif

#ifndef CL
# define CL(x)                     ((x) * 64)
#endif // CL
#ifndef LOG2_CL
# define LOG2_CL                   6#include <string.h>
#endif // LOG2_CL
#ifndef MB
# define MB(x)                     ((x) * 1024 * 1024)
#endif // MB
#ifndef GB
# define GB(x)                     ((x) * MB(1) * 1024)
#endif // GB

END_NAMESPACE(AAL)

//
using namespace AAL;

/// @brief   Define our Runtime client class so that we can receive the runtime started/stopped notifications.
///
/// We implement a Service client within, to handle AAL Service allocation/free.
/// We also implement a Semaphore for synchronization with the AAL runtime.
class RuntimeClient : public CAASBase,
                      public IRuntimeClient
{
public:
   RuntimeClient();
   ~RuntimeClient();

   void end();

   IRuntime* getRuntime();

   btBool isOK();

   // <begin IRuntimeClient interface>
   void runtimeStarted(IRuntime            *pRuntime,
                       const NamedValueSet &rConfigParms);

   void runtimeStopped(IRuntime *pRuntime);

   void runtimeStartFailed(const IEvent &rEvent);

   void runtimeAllocateServiceFailed( IEvent const &rEvent);

   void runtimeAllocateServiceSucceeded(IBase               *pClient,
                                        TransactionID const &rTranID);

   void runtimeEvent(const IEvent &rEvent);
   // <end IRuntimeClient interface>

protected:
   IRuntime        *m_pRuntime;  ///< Pointer to AAL runtime instance.
   Runtime          m_Runtime;   ///< AAL Runtime
   btBool           m_isOK;      ///< Status
   CSemaphore       m_Sem;       ///< For synchronizing with the AAL runtime.
};

class HWService: public CAASBase, public IServiceClient, public ISPLClient
{

public:

	HWService(RuntimeClient * rtc) :
    m_pAALService(NULL),
    m_runtimeClient(rtc),
    m_SPLService(NULL),
    m_Result(0),
    m_AFUDSMVirt(NULL),
    m_AFUCTXVirt(NULL),
    m_AFUCTXPhys(NULL),
    m_AFUCTXSize(0),
    m_AFUDSMSize(0)
    {
      SetSubClassInterface(iidServiceClient, dynamic_cast<IServiceClient *>(this));
      SetInterface(iidSPLClient, dynamic_cast<ISPLClient *>(this));
      SetInterface(iidCCIClient, dynamic_cast<ICCIClient *>(this));
      m_Sem.Create(0, 1);
    }
  ~HWService();

   //--------------- Mandatory Interface methods ------------------------//

   // <ISPLClient>
  virtual void OnTransactionStarted(TransactionID const &TranID,
                                     btVirtAddr AFUDSM,
                                     btWSSize AFUDSMSize);
   virtual void OnContextWorkspaceSet(TransactionID const &TranID);

   virtual void OnTransactionFailed(const IEvent &Event);

   virtual void OnTransactionComplete(TransactionID const &TranID);

   virtual void OnTransactionStopped(TransactionID const &TranID);

   virtual void OnWorkspaceAllocated(TransactionID const &TranID,
                                     btVirtAddr WkspcVirt,
                                     btPhysAddr WkspcPhys,
                                     btWSSize WkspcSize);

   virtual void OnWorkspaceAllocateFailed(const IEvent &Event);

   virtual void OnWorkspaceFreed(TransactionID const &TranID);

   virtual void OnWorkspaceFreeFailed(const IEvent &Event);
   // </ISPLClient>

   // <begin IServiceClient interface>
   void serviceAllocated(IBase *pServiceBase,
                         TransactionID const &rTranID);

   void serviceAllocateFailed(const IEvent &rEvent);

   void serviceFreed(TransactionID const &rTranID);

   void serviceEvent(const IEvent &rEvent);
   // <end IServiceClient interface>
   void   allocHWService();
   bool   allocate_workspace(unsigned int size);

   // Service member objects //
public:
   // Basic objects
   IBase               * m_pAALService;    // The generic AAL Service interface for the AFU.
   RuntimeClient       * m_runtimeClient;
   ISPLAFU             * m_SPLService;
   CSemaphore            m_Sem;            // For synchronizing with the AAL runtime.
   btInt                 m_Result;         // Returned result value; 0 if success

   
   btVirtAddr            m_AFUCTXVirt;     ///
   btPhysAddr            m_AFUCTXPhys;
   btWSSize              m_AFUCTXSize;

   btVirtAddr            m_AFUDSMVirt;     ///< Points to DSM
   btWSSize              m_AFUDSMSize;     ///< Length in bytes of DSM
};


#endif // __PLATFORM_H__