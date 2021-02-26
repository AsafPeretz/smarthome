#ifndef ATOMIC_COUNTER_HPP
#define ATOMIC_COUNTER_HPP

#include "atomic_value.hpp"
#include <stddef.h>

namespace smarthome {

class AtomicCounter {
public:
  explicit AtomicCounter();
  ~AtomicCounter();
  AtomicCounter(const AtomicCounter& a_other);
  AtomicCounter& operator=(const AtomicCounter& a_other);
  void Increase();
  void Decrease();
  size_t Get() const;

private:
  void DecOrDelete ();

private:
  AtomicValue<size_t> *m_counter;

}; // AtomicCounter

}  // smarthome

#endif // ATOMIC_COUNTER_HPP