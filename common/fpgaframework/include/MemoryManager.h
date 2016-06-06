#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

using namespace AAL;

class WorkSpc{
   
 public:

  btVirtAddr     baseVirt;     
  btWSSize       m_WkspcSize;  
  btPhysAddr     basePhys;

  WorkSpc(btVirtAddr virBase, btPhysAddr phBase, btWSSize wsSize){

   	baseVirt    = virBase;
   	m_WkspcSize = wsSize;
   	basePhys    = phBase;
  }

};

class MemoryManagerClient{
public:
	WorkSpc     * appWkSpc;

	btVirtAddr  baseRegister;
	btVirtAddr  limitRegister;
	btVirtAddr  dataBaseRegister;

	MemoryManagerClient(btVirtAddr virBase, btPhysAddr phyBase, btWSSize wsSize ){
		appWkSpc = new WorkSpc(virBase, phyBase, wsSize);

		baseRegister     = virBase;
		dataBaseRegister = virBase + MB(2);
		limitRegister    = virBase + wsSize;
	} 
	//

	btVirtAddr get_virt_base(){ return appWkSpc->baseVirt; }

	void * malloc(unsigned int size_in_bytes){
		//
		if((dataBaseRegister + size_in_bytes) <= limitRegister)
		{
			void * addr   = dataBaseRegister;

			unsigned int inc_bytes = (size_in_bytes%64)? ((size_in_bytes>>6)+1) << 6 : size_in_bytes;
			dataBaseRegister += inc_bytes;

			return addr;
		}
		return NULL;
	}

	void   free(void * ptr){ }

	void reset(){
		baseRegister     = get_virt_base();
		dataBaseRegister = get_virt_base() + MB(2);
	}

};

#endif //__MEMORY_MANAGER_H__