#include "mutex.hpp"
#include <assert.h>
#include <errno.h>
#include <new>

namespace smarthome {
  
  Mutex::Mutex () {
    int status = pthread_mutex_init(&m_mutex, NULL);
    if (0 != status) {
      assert(status != EINVAL);
      assert(status == ENOMEM);
      throw std::bad_alloc();
    }
  }

  Mutex::~Mutex () {
    int status = pthread_mutex_destroy(&m_mutex);
    assert(0 == status);
  }

  void Mutex::Lock () {
    if(0 != pthread_mutex_lock(&m_mutex)) {
      throw mutex::TryToDestroyLockedObjectException();
    }
    return;
  }

  void Mutex::UnLock () {
    if(0 != pthread_mutex_unlock(&m_mutex)) {
      throw mutex::ObjectIsAlreadyUnlockedException();
    }
    return;
  }

} // smarthome