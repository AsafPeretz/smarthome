#ifndef GUARD_MUTEX_HPP
#define GUARD_MUTEX_HPP

#include "mutex.hpp"
#include "uncopyable.hpp"

namespace smarthome {

class GuardMutex : private UnCopyable {
public:
  explicit GuardMutex(Mutex& a_mutex);
  ~GuardMutex();

private:
  Mutex& m_lock;
}; // GuardMutex

}  // smarthome

#endif // GUARD_MUTEX_HPP