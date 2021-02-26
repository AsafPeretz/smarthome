#ifndef ATOMIC_VALUE_INL
#define ATOMIC_VALUE_INL

template<class Value>
AtomicValue<Value>::AtomicValue(const Value& a_val)
: m_value(a_val)
{
}

template<class Value>
AtomicValue<Value>::~AtomicValue() {
}

template<class Value>
AtomicValue<Value>::AtomicValue(const AtomicValue<Value>& a_other) {
  __atomic_store_n(&m_value, a_other.m_value, __ATOMIC_SEQ_CST);
}

template<class Value>
AtomicValue<Value>& AtomicValue<Value>::operator=(const AtomicValue<Value>& a_other) {
  __atomic_store_n(&m_value, a_other.m_value, __ATOMIC_SEQ_CST);
  return *this;
}

template<class Value>
AtomicValue<Value>& AtomicValue<Value>::operator=(const Value& a_val) {
  __atomic_store_n(&m_value, a_val, __ATOMIC_SEQ_CST);
  return *this;
}

template<class Value>
Value AtomicValue<Value>::Get() const {
  return __atomic_load_n(&m_value, __ATOMIC_CONSUME);
}

template<class Value>
Value AtomicValue<Value>::Add(const Value& a_add) {
  return __sync_add_and_fetch(&m_value, a_add);
}

template<class Value>
Value AtomicValue<Value>::Sub(const Value& a_sub) {
  return __sync_sub_and_fetch(&m_value, a_sub);
}

template<class Value>
bool AtomicValue<Value>::Compare(const Value& a_val) const {
  return __sync_bool_compare_and_swap(&m_value, a_val, a_val);
}

template<class Value>
AtomicValue<Value>& AtomicValue<Value>::operator++() {
  this->Add(1);
  return *this;
}

template<class Value>
AtomicValue<Value>& AtomicValue<Value>::operator--() {
  this->Sub(1);
  return *this;
}

#endif // ATOMIC_VALUE_INL
