#ifndef RENDEZVOUS_HPP
#define RENDEZVOUS_HPP

#include "atomic_value.hpp"
#include "cond_var.hpp"
#include "mutex.hpp"

namespace smarthome {

class Rendezvous {
public:
  explicit Rendezvous();
  // ~Rendezvous() = default
  // Rendezvous(const Rendezvous& a_other) = default
  // Rendezvous& operator=(const Rendezvous& a_other) = default
  void Notify();
  void Wait();

private:
  Mutex m_lock;
  CondVar m_cv;
  AtomicValue<bool> m_isArrived;

}; // Rendezvous

} // smarthome

#endif // RENDEZVOUS_HPP
