#include "guard_semaphore.hpp"

namespace smarthome {

Guard_Semaphore::Guard_Semaphore(Semaphore& a_sem)
: m_down(a_sem)
, m_post(1) {
  m_down.DecreaseOrLock();
}

void Guard_Semaphore::Forget() {  
  m_post = 0;
}

Guard_Semaphore::~Guard_Semaphore() {  
  if (m_post) {
    m_down.Increase();
  }
}

} // smarthome