#include "semaphore.hpp"
#include <assert.h>
#include <errno.h>

namespace smarthome {

Semaphore::Semaphore() {
  int status = sem_init(&m_semaphore, 0, 1);
  if (0 != status) {
    assert(errno != ENOSYS);
    assert(errno != EINVAL);
    throw semaphore::UnknownException();
  }
}

Semaphore::Semaphore(unsigned int a_initValue) {
  int status = sem_init(&m_semaphore, 0, a_initValue);
  if (0 != status) {
    assert(errno != ENOSYS);
    if(errno == EINVAL) {
      throw semaphore::ValueOutOfBoundsException();  
    }
    throw semaphore::UnknownException();
  }
}

Semaphore::Semaphore(unsigned int a_initValue, bool a_sharedBetweenProcesses) {
  int status = sem_init(&m_semaphore, a_sharedBetweenProcesses, a_initValue);
  if (0 != status) {
    if(errno == EINVAL) {
      throw semaphore::ValueOutOfBoundsException();
    }
    if(errno == ENOSYS) {
      throw semaphore::SystemDoesntSupportProccesSharedException();  
    }
    throw semaphore::UnknownException();
  }
}

Semaphore::~Semaphore() {
  int status = sem_destroy(&m_semaphore);
  assert(0 == status);
}

void Semaphore::Increase() {
  int status = sem_post(&m_semaphore);
  if(0 != status) {
    assert(errno != EINVAL);
    if(errno == EOVERFLOW) {
      throw semaphore::ValueOutOfBoundsException();  
    }
    throw semaphore::UnknownException();
  }
}

void Semaphore::DecreaseOrLock() {
  int status = sem_wait(&m_semaphore);
  if (0 != status) {
    assert(errno != EINVAL);
    if(errno == EINTR) {
      throw semaphore::WasInterruptedBySignalHandlerException();  
    }
    throw semaphore::UnknownException();
  }
}

} // smarthome