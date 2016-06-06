#ifndef FQUEUE_H
#define FQUEUE_H

#include <aalsdk/kernel/vafu2defs.h>      // AFU structure definitions (brings in spl2defs.h)
#include <thread>
#include <atomic>

#define FQUEUE_VALID_CODE 0x13579bdf

template <typename T>
struct patch16 {
   T d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;
};

template <typename T>
class FQueue{
public: //Everything is public to avoid reordering in memory
  // fields
  union {
        AAL::btUnsigned64bitInt          qword0[8];       // make it a whole cacheline
        struct {
            T                       *m_buffer; 
            //btUnsigned32bitInt       m_size;
            volatile AAL::btUnsigned32bitInt       m_capacity;
            volatile AAL::btUnsigned32bitInt       m_capacity_bytes;
            volatile AAL::btUnsigned32bitInt       update_bytes_rate;
            volatile AAL::btUnsigned32bitInt       m_crb_code;
        };
    };

  // producer info
  union {
        AAL::btUnsigned64bitInt          qword1[8];       // make it a whole cacheline
        struct {
            volatile AAL::btUnsigned32bitInt       m_producer_idx;
            volatile AAL::btUnsigned32bitInt       m_producer_bytes;
            volatile AAL::btUnsigned32bitInt       m_producer_code;
            volatile bool                          m_producer_done;
        };
  };

  // consumer info
  union {
        AAL::btUnsigned64bitInt          qword2[8];       // make it a whole cacheline
        struct {
            volatile AAL::btUnsigned32bitInt       m_consumer_idx;
            volatile AAL::btUnsigned32bitInt       m_consumer_bytes;
        };
  };
    // Constructor
    //FQueue<T>(ServiceHW *srvHndle, unsigned int capacity); //TODO

  bool push(T value);
  bool pop(T& value);
  bool empty();
  bool full();
  std::size_t size() const;
  std::size_t capacity() const;

  void done();
  bool isDone();
  void reset();

};

/*template <typename T>
FQueue::FQueue(ServiceHW *srvHndle, unsigned int capacity)
{
      unsigned int num_cl = (capacity+63 / 64); //TODO check rounding
      m_buffer          = (btVirtAddr)(srvHndle->malloc(CL(num_cl))); //TODO this should be done by the allocator!!!
      //m_size        = 0;
      m_capacity = capacity;
      m_capacity_bytes = capacity * sizeof(T);

      m_producer_idx = 0;
      m_producer_bytes = 0;
      m_producer_done = false;
      m_consumer_idx = 0;
      m_consumer_bytes = 0;
}*/

// TODO deconstructor

template <typename T>
bool FQueue<T>::push( T value)
{
  // Check if full
  while  ( full() )
  {
  SleepNano(100);
   // return false;
  }
  //insert at end
  atomic_thread_fence(std::memory_order_acquire);
  //memcpy(&(m_buffer[m_producer_idx]), &value, sizeof(struct patch16<T>) );
  m_buffer[m_producer_idx] = value;
 // m_producer_bytes += sizeof(T);
  m_producer_idx = (m_producer_idx + 1) % m_capacity;
  m_producer_bytes += sizeof(T);
  
  atomic_thread_fence(std::memory_order_release);
 // m_producer_idx = (m_producer_idx + 1) % m_capacity;
  return true;
}

template <typename T>
bool FQueue<T>::pop(T & value)
{
  // Check if empty
  while ( empty() )
  {
    SleepNano(100);
   // return false;
  }
  atomic_thread_fence(std::memory_order_acquire);
  //memcpy( &value, &(m_buffer[m_consumer_idx]), sizeof(struct patch16<T>) );
  value = m_buffer[m_consumer_idx];
 // m_consumer_bytes += sizeof(T);
  m_consumer_idx  = (m_consumer_idx + 1) % m_capacity;
  m_consumer_bytes += sizeof(T);
  atomic_thread_fence(std::memory_order_release);
 // m_consumer_idx = (m_consumer_idx + 1) % m_capacity;
  
  return true;
}

template <typename T>
bool FQueue<T>::empty()
{

  if( (m_producer_bytes - m_consumer_bytes)  < sizeof(T) )
  {
  /*  MSG("m_producer_bytes = " << m_producer_bytes <<"\n" <<
      "m_consumer_bytes = " << m_consumer_bytes <<"\n" <<
      "Data type size = " << sizeof(T) << "\n" <<
      "capacity_bytes = " << m_capacity_bytes <<"\n"
    );
*/
    return true;

  } 
  return (m_producer_bytes == m_consumer_bytes);
 // return (m_producer_idx == m_consumer_idx);
}

template <typename T>
bool FQueue<T>::full()
{
  if( (m_capacity_bytes - (m_producer_bytes - m_consumer_bytes) ) < sizeof(T) ) return true;
  return ((m_producer_bytes - m_consumer_bytes) == m_capacity_bytes);
  //return (((m_producer_idx + 1) % m_capacity) == m_consumer_idx);
}

template <typename T>
size_t FQueue<T>::size() const
{
  return (m_capacity_bytes - (m_producer_bytes - m_consumer_bytes));
}

template <typename T>
size_t FQueue<T>::capacity() const
{
  return m_capacity;
}

template <typename T>
void FQueue<T>::done()
{
   m_producer_done = true;
   m_producer_code = 0xffffffff;
}

template <typename T>
bool FQueue<T>::isDone()
{
   return m_producer_done;
}

template <typename T>
void FQueue<T>::reset()
{
   m_producer_idx    = 0;
   m_producer_bytes  = 0;
   m_producer_done   = false;
   m_consumer_idx    = 0;
   m_consumer_bytes  = 0;
}

#endif
