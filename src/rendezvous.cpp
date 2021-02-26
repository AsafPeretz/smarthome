#include "rendezvous.hpp"
#include "guard_mutex.hpp"
#include "cassert"

namespace smarthome {

class CheckArrived {
public:
  CheckArrived(const AtomicValue<bool>& a_arrived)
  : m_isArrived(a_arrived)
  {
  }
  bool operator()() const{
    return !m_isArrived.Get();
  }
private:
  const AtomicValue<bool>& m_isArrived;
}; // CheckArrived

Rendezvous::Rendezvous()
: m_lock()
, m_cv()
, m_isArrived(false)
{
}

void Rendezvous::Notify() {
  GuardMutex Guard(m_lock);
  m_isArrived = true;
  m_cv.BroadCast();
}

void Rendezvous::Wait() {
  GuardMutex Guard(m_lock);
  if (m_isArrived.Get()) {
    return;
  }
  CheckArrived pred(m_isArrived);
  m_cv.Wait<CheckArrived>(m_lock, pred);
  assert(m_isArrived.Get());
}

} // smarthome
