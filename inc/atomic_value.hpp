#ifndef ATOMIC_VALUE_HPP
#define ATOMIC_VALUE_HPP

namespace smarthome {

template<class Value>
class AtomicValue {
public:
  explicit AtomicValue(const Value& a_val);
  ~AtomicValue();
  AtomicValue(const AtomicValue<Value>& a_other);
  AtomicValue<Value>& operator=(const AtomicValue<Value>& a_other);
  AtomicValue<Value>& operator=(const Value& a_other);
  Value Get() const;
  Value Add(const Value& a_val);
  Value Sub(const Value& a_val);
  bool Compare(const Value& a_val) const;
  AtomicValue<Value>& operator++();
  AtomicValue<Value>& operator--();

private:
  mutable Value m_value;
}; // AtomicValue

#include "./inl/atomic_value.inl"

}  // smarthome

#endif // ATOMIC_VALUE_HPP
