#include "atomic_counter.hpp"

namespace smarthome {

AtomicCounter::AtomicCounter()
: m_counter(new AtomicValue<size_t>(1)) {
}

AtomicCounter::~AtomicCounter() {
  DecOrDelete();
}

AtomicCounter::AtomicCounter(const AtomicCounter& a_other)
: m_counter(a_other.m_counter) {
  ++(*m_counter);
}

AtomicCounter& AtomicCounter::operator=(const AtomicCounter& a_other) {
  ++(*a_other.m_counter);
  Decrease();
  m_counter = a_other.m_counter;
  return *this;
}

void AtomicCounter::Increase() {
  ++(*m_counter);
}

void AtomicCounter::Decrease() {
  DecOrDelete();
}

size_t AtomicCounter::Get() const {
  return (*m_counter).Get();
}


/* --------------- Private Functions --------------- */

void AtomicCounter::DecOrDelete () {
  --(*m_counter);
  if (m_counter->Compare(0)) {
    delete m_counter;
  }
}

} // smarthome
