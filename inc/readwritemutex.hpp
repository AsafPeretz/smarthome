#ifndef READWRITEMUTEX_HPP
#define READWRITEMUTEX_HPP

#include <pthread.h>
#include "mutex.hpp"
#include "semaphore.hpp"

namespace smarthome {

class ReadWrite_Mutex {
public:
  ReadWrite_Mutex();
  ~ReadWrite_Mutex();
  void Lock();
  void Unlock();
  void IncWriters();
  void DecWriters();
  void IncReaders();
  void DecReaders();
  void WaitForReaders();
  void WaitForWriters();
private:
  pthread_mutex_t m_sources;
  pthread_cond_t m_allWritersOut;
  pthread_cond_t m_allReadersOut;
  size_t m_numOfWriters;
  size_t m_numOfReaders;
}; // ReadWrite_Mutex

}  // smarthome

#endif // READWRITEMUTEX_HPP