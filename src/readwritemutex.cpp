#include "readwritemutex.hpp"

namespace smarthome {

ReadWrite_Mutex::ReadWrite_Mutex()
: m_sources()
, m_allWritersOut()
, m_allReadersOut()
, m_numOfWriters(0)
, m_numOfReaders(0) {
}

ReadWrite_Mutex::~ReadWrite_Mutex() {
}

void ReadWrite_Mutex::Lock() {
  pthread_mutex_lock(&m_sources);
}

void ReadWrite_Mutex::Unlock() {
  pthread_mutex_unlock(&m_sources);
}

void ReadWrite_Mutex::IncWriters() {
  pthread_mutex_lock(&m_sources);
  while (0 != m_numOfReaders) {
    pthread_cond_wait(&m_allReadersOut, &m_sources);
  }
  ++m_numOfWriters;
}

void ReadWrite_Mutex::DecWriters() {
  --m_numOfWriters;
  pthread_cond_signal(&m_allWritersOut);
  pthread_mutex_unlock(&m_sources);
}

void ReadWrite_Mutex::IncReaders() {
  pthread_mutex_lock(&m_sources);
  while (0 != m_numOfWriters) {
    pthread_cond_wait(&m_allWritersOut, &m_sources);
  }
  ++m_numOfReaders;
  pthread_cond_signal(&m_allReadersOut);
  pthread_mutex_unlock(&m_sources);
}

void ReadWrite_Mutex::DecReaders() {
  --m_numOfReaders;
  pthread_cond_signal(&m_allWritersOut);  
}

void ReadWrite_Mutex::WaitForReaders() {
  while (0 != m_numOfReaders) {
    pthread_cond_wait(&m_allReadersOut, &m_sources);
  }
}

void ReadWrite_Mutex::WaitForWriters() {
  while (0 != m_numOfWriters) {
    pthread_cond_wait(&m_allWritersOut, &m_sources);
  }
}

}  // smarthome
