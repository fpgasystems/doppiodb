#ifndef __cplusplus
#include "fpga.h"
#endif
#include "fpga.hpp"



// Copyright (c) 2007-2015, Intel Corporation
//
// Redistribution  and  use  in source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of  source code  must retain the  above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name  of Intel Corporation  nor the names of its contributors
//   may be used to  endorse or promote  products derived  from this  software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
// IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT  SHALL THE COPYRIGHT OWNER  OR CONTRIBUTORS BE
// LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
// CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED  TO,  PROCUREMENT  OF
// SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE,  DATA, OR PROFITS;  OR BUSINESS
// INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY  OF LIABILITY,  WHETHER IN
// CONTRACT,  STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE  OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//****************************************************************************
/// @file HelloSPLLB.cpp
/// @brief Basic SPL AFU interaction.
/// @ingroup HelloSPLLB
/// @verbatim
/// Intel(R) QuickAssist Technology Accelerator Abstraction Layer Sample Application
///
///    This application is for example purposes only.
///    It is not intended to represent a model for developing commercially-deployable applications.
///    It is designed to show working examples of the AAL programming model and APIs.
///
/// AUTHORS: Joseph Grecco, Intel Corporation.
///
/// This Sample demonstrates the following:
///    - The basic structure of an AAL program using the AAL Runtime APIs.
///    - The ISPLAFU and ISPLClient interfaces of the SPLAFU Service.
///    - System initialization and shutdown.
///    - Use of interface IDs (iids).
///    - Accessing object interfaces through the Interface functions.
///
/// This sample is designed to be used with the SPLAFU Service.
///
/// HISTORY:
/// WHEN:          WHO:     WHAT:
/// 06/15/2015     JG       Initial version started based on older sample code.@endverbatim
//****************************************************************************
//#include <aalsdk/AAL.h>
//#include <aalsdk/xlRuntime.h>
//#include <aalsdk/AALLoggerExtern.h> // Logger

//#include <aalsdk/service/ISPLAFU.h>       // Service Interface
//#include <aalsdk/service/ISPLClient.h>    // Service Client Interface
//#include <aalsdk/kernel/vafu2defs.h>      // AFU structure definitions (brings in spl2defs.h)

//#include <string.h>

//****************************************************************************
// UN-COMMENT appropriate #define in order to enable either Hardware or ASE.
//    DEFAULT is to use Software Simulation.
//****************************************************************************
// #define  HWAFU
#define  ASEAFU

using namespace AAL;

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
# define LOG2_CL                   6
#endif // LOG2_CL
#ifndef MB
# define MB(x)                     ((x) * 1024 * 1024)
#endif // MB
#define LPBK1_BUFFER_SIZE        CL(1)

#define LPBK1_DSM_SIZE           MB(4)

/// @addtogroup HelloSPLLB
/// @{

//int tbl_nlen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
//char* tbl_name[8];
//int tbl_offs[8];
//int tbl_len[8];

//int fp_scan_offset = 0;
//int fp_scan_length = 0;
void* fp_base_address;
void* fp_curr_address;
size_t fp_workspace_size;

void* theApp;
void* runtimeClient;

/// @brief   Define our Runtime client class so that we can receive the runtime started/stopped notifications.
///
/// We implement a Service client within, to handle AAL Service allocation/free.
/// We also implement a Semaphore for synchronization with the AAL runtime.
class RuntimeClient: public CAASBase, public IRuntimeClient {
public:
	RuntimeClient();
	~RuntimeClient();

	void end();

	IRuntime* getRuntime();

	btBool isOK();

	// <begin IRuntimeClient interface>
	void runtimeStarted(IRuntime *pRuntime, const NamedValueSet &rConfigParms);

	void runtimeStopped(IRuntime *pRuntime);

	void runtimeStartFailed(const IEvent &rEvent);

	void runtimeAllocateServiceFailed(IEvent const &rEvent);

	void runtimeAllocateServiceSucceeded(IBase *pClient,
			TransactionID const &rTranID);

	void runtimeEvent(const IEvent &rEvent);
	// <end IRuntimeClient interface>

protected:
	IRuntime *m_pRuntime;  ///< Pointer to AAL runtime instance.
	Runtime m_Runtime;   ///< AAL Runtime
	btBool m_isOK;      ///< Status
	CSemaphore m_Sem;       ///< For synchronizing with the AAL runtime.
};

///////////////////////////////////////////////////////////////////////////////
///
///  MyRuntimeClient Implementation
///
///////////////////////////////////////////////////////////////////////////////
RuntimeClient::RuntimeClient() :
		m_Runtime(),        // Instantiate the AAL Runtime
		m_pRuntime(NULL), m_isOK(false) {
	NamedValueSet configArgs;
	NamedValueSet configRecord;

	// Publish our interface
	SetSubClassInterface(iidRuntimeClient,
			dynamic_cast<IRuntimeClient *>(this));

	m_Sem.Create(0, 1);

	// Using Hardware Services requires the Remote Resource Manager Broker Service
	//  Note that this could also be accomplished by setting the environment variable
	//   XLRUNTIME_CONFIG_BROKER_SERVICE to librrmbroker
#if defined( HWAFU )
	configRecord.Add(XLRUNTIME_CONFIG_BROKER_SERVICE, "librrmbroker");
	configArgs.Add(XLRUNTIME_CONFIG_RECORD,configRecord);
#endif

	if (!m_Runtime.start(this, configArgs)) {
		m_isOK = false;
		return;
	}
	m_Sem.Wait();
}

RuntimeClient::~RuntimeClient() {
	m_Sem.Destroy();
}

btBool RuntimeClient::isOK() {
	return m_isOK;
}

void RuntimeClient::runtimeStarted(IRuntime *pRuntime,
		const NamedValueSet &rConfigParms) {
	// Save a copy of our runtime interface instance.
	m_pRuntime = pRuntime;
	m_isOK = true;
	m_Sem.Post(1);
}

void RuntimeClient::end() {
	m_Runtime.stop();
	m_Sem.Wait();
}

void RuntimeClient::runtimeStopped(IRuntime *pRuntime) {
	MSG("Runtime stopped");
	m_isOK = false;
	m_Sem.Post(1);
}

void RuntimeClient::runtimeStartFailed(const IEvent &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("Runtime start failed");
	ERR(pExEvent->Description());
}

void RuntimeClient::runtimeAllocateServiceFailed(IEvent const &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("Runtime AllocateService failed");
	ERR(pExEvent->Description());
}

void RuntimeClient::runtimeAllocateServiceSucceeded(IBase *pClient,
		TransactionID const &rTranID) {
	MSG("Runtime Allocate Service Succeeded");
}

void RuntimeClient::runtimeEvent(const IEvent &rEvent) {
	MSG("Generic message handler (runtime)");
}

IRuntime * RuntimeClient::getRuntime() {
	return m_pRuntime;
}

/// @brief   Define our Service client class so that we can receive Service-related notifications from the AAL Runtime.
///          The Service Client contains the application logic.
///
/// When we request an AFU (Service) from AAL, the request will be fulfilled by calling into this interface.
class HelloSPLLBApp: public CAASBase, public IServiceClient, public ISPLClient {
public:

	HelloSPLLBApp(RuntimeClient * rtc);
	~HelloSPLLBApp();

	void run();
	void stop();
	void Show2CLs(void *pCLExpected, void *pCLFound, ostringstream &oss);
	void _DumpCL(void *pCL, ostringstream &oss);

	// <ISPLClient>
	virtual void OnTransactionStarted(TransactionID const &TranID,
			btVirtAddr AFUDSM, btWSSize AFUDSMSize);
	virtual void OnContextWorkspaceSet(TransactionID const &TranID);

	virtual void OnTransactionFailed(const IEvent &Event);

	virtual void OnTransactionComplete(TransactionID const &TranID);

	virtual void OnTransactionStopped(TransactionID const &TranID);
	virtual void OnWorkspaceAllocated(TransactionID const &TranID,
			btVirtAddr WkspcVirt, btPhysAddr WkspcPhys, btWSSize WkspcSize);

	virtual void OnWorkspaceAllocateFailed(const IEvent &Event);

	virtual void OnWorkspaceFreed(TransactionID const &TranID);

	virtual void OnWorkspaceFreeFailed(const IEvent &Event);
	// </ISPLClient>

	// <begin IServiceClient interface>
	virtual void serviceAllocated(IBase *pServiceBase,
			TransactionID const &rTranID);

	virtual void serviceAllocateFailed(const IEvent &rEvent);

	virtual void serviceFreed(TransactionID const &rTranID);

	virtual void serviceEvent(const IEvent &rEvent);
	// <end IServiceClient interface>

protected:
	IBase *m_pAALService;    // The generic AAL Service interface for the AFU.
	RuntimeClient *m_runtimClient;
	ISPLAFU *m_SPLService;
	CSemaphore m_Sem;            // For synchronizing with the AAL runtime.
	btInt m_Result;

	// Workspace info
	btVirtAddr m_pWkspcVirt;     ///< Workspace virtual address.
	btWSSize m_WkspcSize;      ///< DSM workspace size in bytes.

	btVirtAddr m_AFUDSMVirt;     ///< Points to DSM
	btWSSize m_AFUDSMSize;     ///< Length in bytes of DSM
};

///////////////////////////////////////////////////////////////////////////////
///
///  Implementation
///
///////////////////////////////////////////////////////////////////////////////
HelloSPLLBApp::HelloSPLLBApp(RuntimeClient *rtc) :
		m_pAALService(NULL), m_runtimClient(rtc), m_SPLService(NULL), m_Result(
				0), m_pWkspcVirt(NULL), m_WkspcSize(0), m_AFUDSMVirt(NULL), m_AFUDSMSize(
				0) {
	SetSubClassInterface(iidServiceClient,
			dynamic_cast<IServiceClient *>(this));
	SetInterface(iidSPLClient, dynamic_cast<ISPLClient *>(this));
	SetInterface(iidCCIClient, dynamic_cast<ICCIClient *>(this));
	m_Sem.Create(0, 1);
}

HelloSPLLBApp::~HelloSPLLBApp() {
	m_Sem.Destroy();
}

void HelloSPLLBApp::run() {
	cout << "=======================" << endl;
	cout << "= Hello SPL LB Sample =" << endl;
	cout << "=======================" << endl;

	// Request our AFU.

	// NOTE: This example is bypassing the Resource Manager's configuration record lookup
	//  mechanism.  This code is work around code and subject to change.
	NamedValueSet Manifest;
	NamedValueSet ConfigRecord;

#if defined( HWAFU )                /* Use FPGA hardware */
	ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME, "libHWSPLAFU");
	ConfigRecord.Add(keyRegAFU_ID,"00000000-0000-0000-0000-000011100181");
	ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_AIA_NAME, "libAASUAIA");

#elif defined ( ASEAFU )
	ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME,
			"libASESPLAFU");
	ConfigRecord.Add(AAL_FACTORY_CREATE_SOFTWARE_SERVICE, true);

#else

	ConfigRecord.Add(AAL_FACTORY_CREATE_CONFIGRECORD_FULL_SERVICE_NAME, "libSWSimSPLAFU");
	ConfigRecord.Add(AAL_FACTORY_CREATE_SOFTWARE_SERVICE,true);
#endif

	Manifest.Add(AAL_FACTORY_CREATE_CONFIGRECORD_INCLUDED, ConfigRecord);

	Manifest.Add(AAL_FACTORY_CREATE_SERVICENAME, "Hello SPL LB");

	MSG("Allocating Service");

	// Allocate the Service and allocate the required workspace.
	//   This happens in the background via callbacks (simple state machine).
	//   When everything is set we do the real work here in the main thread.
	m_runtimClient->getRuntime()->allocService(dynamic_cast<IBase *>(this),
			Manifest);

	m_Sem.Wait();

	btVirtAddr pWSUsrVirt = m_pWkspcVirt; // Address of Workspace
	const btWSSize WSLen = m_WkspcSize; // Length of workspace

	MSG(
			"Allocated " << WSLen << "-byte Workspace at virtual address " << std::hex << (void *)pWSUsrVirt);

	memset(pWSUsrVirt, 0x00, WSLen);

	btVirtAddr pSource = pWSUsrVirt + sizeof(REGEX_CNTXT);// + 32; // the 32 byte offset is to push postgres into the right cache line allignment

	// The destination buffer is right after the source buffer
	//fp_virtual_output_area = pWSUsrVirt+MB(1025);

	REGEX_CNTXT *pREGEX_cntxt = reinterpret_cast<REGEX_CNTXT *>(pWSUsrVirt);

	memset(pREGEX_cntxt, 0, sizeof(REGEX_CNTXT));
	pREGEX_cntxt->num_bat = 0; // the AFU will block here
   //THIS is just for legacy
	pREGEX_cntxt->pSource = pSource;
	pREGEX_cntxt->pDest = pSource;//fp_virtual_output_area;

	fp_base_address = pWSUsrVirt;
   fp_curr_address = pSource;
   fp_workspace_size = MB(2048);

	MSG("Starting SPL Transaction with Workspace");
	m_SPLService->StartTransactionContext(TransactionID(), pWSUsrVirt, 100);
	m_Sem.Wait();

	//return pSource;

}

void HelloSPLLBApp::stop() {


     MSG("Workspace verification complete, freeing workspace.");
     m_SPLService->WorkspaceFree(((btVirtAddr)fp_base_address), TransactionID());
     m_Sem.Wait();

     m_runtimClient->end();
}

// We must implement the IServiceClient interface (IServiceClient.h):

// <begin IServiceClient interface>
void HelloSPLLBApp::serviceAllocated(IBase *pServiceBase,
		TransactionID const &rTranID) {
	m_pAALService = pServiceBase;
	ASSERT(NULL != m_pAALService);

	// Documentation says SPLAFU Service publishes ISPLAFU as subclass interface
	m_SPLService = subclass_ptr<ISPLAFU>(pServiceBase);

	ASSERT(NULL != m_SPLService);
	if ( NULL == m_SPLService) {
		return;
	}

	MSG("Service Allocated");

	// Allocate Workspaces needed. ASE runs more slowly and we want to watch the transfers,
	//   so have fewer of them.
#if defined ( ASEAFU )
#define LB_BUFFER_SIZE MB(1020)
#else
#define LB_BUFFER_SIZE MB(1020)
#endif

	m_SPLService->WorkspaceAllocate(
			sizeof(REGEX_CNTXT) + LB_BUFFER_SIZE + LB_BUFFER_SIZE/10,
			TransactionID());

}

void HelloSPLLBApp::serviceAllocateFailed(const IEvent &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("Failed to allocate a Service");
	ERR(pExEvent->Description());
	m_Sem.Post(1);
}

void HelloSPLLBApp::serviceFreed(TransactionID const &rTranID) {
	MSG("Service Freed");
	// Unblock Main()
	m_Sem.Post(1);
}

// <ISPLClient>
void HelloSPLLBApp::OnWorkspaceAllocated(TransactionID const &TranID,
		btVirtAddr WkspcVirt, btPhysAddr WkspcPhys, btWSSize WkspcSize) {
	AutoLock(this);

	m_pWkspcVirt = WkspcVirt;
	m_WkspcSize = WkspcSize;

	MSG("Got Workspace");         // Got workspace so unblock the Run() thread
	m_Sem.Post(1);
}

void HelloSPLLBApp::OnWorkspaceAllocateFailed(const IEvent &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("OnWorkspaceAllocateFailed");
	ERR(pExEvent->Description());
	++m_Result;
	m_Sem.Post(1);
}

void HelloSPLLBApp::OnWorkspaceFreed(TransactionID const &TranID) {
	MSG("OnWorkspaceFreed");
	// Freed so now Release() the Service through the Services IAALService::Release() method
	(dynamic_ptr<IAALService>(iidService, m_pAALService))->Release(
			TransactionID());
}

void HelloSPLLBApp::OnWorkspaceFreeFailed(const IEvent &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("OnWorkspaceAllocateFailed");
	ERR(pExEvent->Description());
	++m_Result;
	m_Sem.Post(1);
}

/// CMyApp Client implementation of ISPLClient::OnTransactionStarted
void HelloSPLLBApp::OnTransactionStarted(TransactionID const &TranID,
		btVirtAddr AFUDSMVirt, btWSSize AFUDSMSize) {
	MSG("Transaction Started");
	m_AFUDSMVirt = AFUDSMVirt;
	m_AFUDSMSize = AFUDSMSize;
	m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnContextWorkspaceSet
void HelloSPLLBApp::OnContextWorkspaceSet(TransactionID const &TranID) {
	MSG("Context Set");
	m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnTransactionFailed
void HelloSPLLBApp::OnTransactionFailed(const IEvent &rEvent) {
	IExceptionTransactionEvent * pExEvent = dynamic_ptr<
			IExceptionTransactionEvent>(iidExTranEvent, rEvent);
	ERR("Runtime AllocateService failed");
	ERR(pExEvent->Description());
	m_bIsOK = false;
	++m_Result;
	m_AFUDSMVirt = NULL;
	m_AFUDSMSize = 0;
	ERR("Transaction Failed");
	m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnTransactionComplete
void HelloSPLLBApp::OnTransactionComplete(TransactionID const &TranID) {
	m_AFUDSMVirt = NULL;
	m_AFUDSMSize = 0;
	MSG("Transaction Complete");
	m_Sem.Post(1);
}
/// CMyApp Client implementation of ISPLClient::OnTransactionStopped
void HelloSPLLBApp::OnTransactionStopped(TransactionID const &TranID) {
	m_AFUDSMVirt = NULL;
	m_AFUDSMSize = 0;
	MSG("Transaction Stopped");
	m_Sem.Post(1);
}
void HelloSPLLBApp::serviceEvent(const IEvent &rEvent) {
	ERR("unexpected event 0x" << hex << rEvent.SubClassID());
}
// <end IServiceClient interface>

void HelloSPLLBApp::Show2CLs(void *pCLExpected, // pointer to cache-line expected
		void *pCLFound,    // pointer to found cache line
		ostringstream &oss)         // add it to this ostringstream
		{
	oss << "Expected: ";
	_DumpCL(pCLExpected, oss);
	oss << "\n";
	oss << "Found:    ";
	_DumpCL(pCLFound, oss);
}  // _DumpCL

void HelloSPLLBApp::_DumpCL(void *pCL,  // pointer to cache-line to print
		ostringstream &oss)  // add it to this ostringstream
		{
	oss << std::hex << std::setfill('0') << std::uppercase;
	btUnsigned32bitInt *pu32 = reinterpret_cast<btUnsigned32bitInt*>(pCL);
	for (int i = 0; i < ( CL(1) / sizeof(btUnsigned32bitInt)); ++i) {
		oss << "0x" << std::setw(8) << *pu32 << " ";
		++pu32;
	}
	oss << std::nouppercase;
}  // _DumpCL

/// @} group HelloSPLLB


//TODO maybe call this from BBPinit
extern "C" {
void fpga_init() {

	runtimeClient = new RuntimeClient();
	theApp = new HelloSPLLBApp((RuntimeClient*)runtimeClient);



	if (!((RuntimeClient*)runtimeClient)->isOK()) {
		ERR("Runtime Failed to Start");
		exit(1);
	}
	((HelloSPLLBApp*)theApp)->run();

	MSG("FPGA INIT DONE");
	//return Result;
}

void* FPGAmalloc(size_t size)
{
   if (!runtimeClient)
   {
      fpga_init();
   }
   //Round up to cache lines
   size_t numCL = (size + 63) / 64;
   size_t mysize = numCL * 64;
   printf("FPGAmalloc reqsize: %u, mysize: %u, curr: %p, base: %p, size: %u\n", size, mysize, fp_curr_address, fp_base_address, fp_workspace_size);
   fflush(stdout);
   if ((fp_curr_address + mysize) <= (fp_base_address + fp_workspace_size))
   {
      void* addr = fp_curr_address;
      fp_curr_address += mysize;
      MSG("FPGA ALLOC: SUCCESS");
      printf("addr: %p\n", addr);
      fflush(stdout);
      return addr;
   }
      
   MSG("FPGA ALLOC: FAIL");
   return NULL; 
}

void* FPGAmallocmax(size_t size, size_t *maxsize, int emergency)
{
   if (!runtimeClient)
   {
      fpga_init();
   }
   //Round up to cache lines
   //*maxsize = (size + 63) / 64;
   size_t numCL = (size + 63) / 64;
   size_t mysize = numCL * 64;
   printf("FPGAmallocmax reqsize: %u, mysize: %u, curr: %p, base: %p, size: %u\n", size, mysize, fp_curr_address, fp_base_address, fp_workspace_size);
   fflush(stdout);
   if ((fp_curr_address + mysize) <= (fp_base_address + fp_workspace_size))
   {
      void* addr = fp_curr_address;
      fp_curr_address += mysize;
      *maxsize = mysize;
      MSG("FPGA ALLOC: SUCCESS");
      printf("addr: %p\n", addr);
      fflush(stdout);
      return addr;
   }
      
   MSG("FPGA ALLOC: FAIL");
   return NULL; 
}

void* FPGAreallocmax(void* ptr, size_t size, size_t *psize, int emergency)
{
   //TODO On shrink do not change pointer!!
   void* newaddr = FPGAmallocmax(size, psize, emergency);
   if (newaddr)
   {
      memcpy(newaddr, ptr, size);
      return newaddr;
   }
   MSG("FPGA REALLOC: FAIL");
   return NULL;
}

void FPGAfree(void *blk)
{
   ssize_t size = 0;
   ssize_t *s = (ssize_t*) blk;
   if (s == NULL)
      return;
   //size = GDK_MEM_BLKSIZE(s);
   //TODO reinsert this chunck
}

//MAYBE add GDK_VAROFFSET
void FPGAregex(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               void* retBase)
{
   MSG("Processing on FPGA...");
   printf("base: %p\n", base);
   printf("base: %p\n", vbase);
   fflush(stdout);

   volatile REGEX_CNTXT *pREGEX_cntxt = reinterpret_cast<REGEX_CNTXT*>(fp_base_address);
   pREGEX_cntxt->pDest = retBase;
   pREGEX_cntxt->pBase = base;
   pREGEX_cntxt->pVBase = vbase;
   pREGEX_cntxt->tail_width = width;
   //triggers execution on FPGA
   pREGEX_cntxt->num_bat = count;


   SleepMicro(1);
   while (pREGEX_cntxt->num_bat != 0)
   {
      SleepMicro(1);
   }

   MSG("FPGA done.");

   return;
}

/*void fpga_free() {
	((HelloSPLLBApp*)theApp)->stop();
}

int fpga_process(char* name, int nlen) {
	char namecopy[nlen + 1];
	memcpy(namecopy, name, nlen);
	namecopy[nlen] = 0;

	for (int idx = 0; idx < 8; idx++) {

		if (tbl_nlen[idx] == nlen && strcmp(namecopy, tbl_name[idx]) == 0) {

			MSG("Running...");

			volatile VAFU2_CNTXT *pVAFU2_cntxt = reinterpret_cast<VAFU2_CNTXT *>(fp_virtual_pointer);

			pVAFU2_cntxt->pSource = (void*) (tbl_offs[idx]+fp_virtual_pointer);
			pVAFU2_cntxt->num_cl = (tbl_len[idx]/8192);
			pVAFU2_cntxt->pDest = fp_virtual_output_area;

			/*printf("vp: %16lx -- offs: %ld\n", fp_virtual_pointer, tbl_offs[idx]);

			printf("   0: ");
			for (int x=0; x<8192; x++) {

				printf("%2x ", ((uint8_t*)(pVAFU2_cntxt->pSource))[x]);
				if (x%64==63) {
					printf("\n%4d: ",(x+1)/64);
				}
			}*/

			/*while (pVAFU2_cntxt->num_cl!=0) {
				SleepMicro(1);
			}


			MSG("Result:");
			uint8_t* outPoint = (uint8_t*) (fp_virtual_output_area);

			for (int x=0; x<64*64; x++) {

							printf("%2x ", outPoint[x]);
							if (x%64==63) {
								printf("\n%4d: ",(x+1)/64);
							}
			}

			return outPoint[0];


		}

	}

	return -1;

}

int fpga_set_offset(int offs) {
	fp_scan_offset = (uint8_t*) offs - ((uint8_t*) fp_virtual_pointer);
	return 0;
}

int fpga_set_length(int len) {
	fp_scan_length = len;
	return 0;
}

int fpga_set_tablename(char* name, int nlen) {
	int idx = 0;
	while (idx < 8 && tbl_nlen[idx] > 0) {
		idx++;
	}

	if (idx == 8)
		return -1;

	tbl_nlen[idx] = nlen;
	tbl_name[idx] = new char[nlen + 1];
	memcpy(tbl_name[idx], name, nlen);
	tbl_name[idx][nlen] = 0;
	tbl_offs[idx] = fp_scan_offset;
	tbl_len[idx] = fp_scan_length;

	printf("scan_offs: %16lx -- scan_len: %16lx\n", fp_scan_offset, fp_scan_length);

	return 1;
}*/

} //extern C
