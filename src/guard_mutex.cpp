#include "guard_mutex.hpp"

namespace smarthome {

GuardMutex::GuardMutex(Mutex& a_mutex)
: m_lock(a_mutex) {
  m_lock.Lock();
}

GuardMutex::~GuardMutex() {  
  m_lock.UnLock();
}

} // smarthome