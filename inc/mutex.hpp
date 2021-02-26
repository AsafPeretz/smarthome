#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <exception>
#include "uncopyable.hpp"

namespace smarthome {

namespace mutex {
struct TryToDestroyLockedObjectException : public std::exception {
};
struct ObjectIsAlreadyUnlockedException : public std::exception {
};
} // exceptions

class Mutex {
public:
  explicit Mutex();
  ~Mutex();
  // Mutex(const Mutex& a_other) = default
  // Mutex& operator=(const Mutex& a_other) = default
  void Lock();
  void UnLock();

private:
  pthread_mutex_t m_mutex;
  
  friend class CondVar;

}; // Mutex
} // smarthome

#endif // MUTEX_HPP
