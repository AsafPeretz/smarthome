#ifndef SHAREDPTR_INL
#define SHAREDPTR_INL

template<class ValType, class Counter>
SharedPtr<ValType, Counter>::SharedPtr(ValType* a_value)
: m_ptr(a_value)
, m_numOfInstances() {  
}

template<class ValType, class Counter>
SharedPtr<ValType, Counter>::SharedPtr(const SharedPtr& a_other)
: m_ptr(a_other.m_ptr)
, m_numOfInstances(a_other.m_numOfInstances) {
}

template<class ValType, class Counter>
SharedPtr<ValType, Counter>::~SharedPtr() {
  remove();
}

template<class ValType, class Counter>
SharedPtr<ValType, Counter>& SharedPtr<ValType, Counter>::operator=(const SharedPtr& a_other) {
  remove();
  m_ptr = a_other.m_ptr;
  m_numOfInstances = a_other.m_numOfInstances;
  return *this;
}

template<class ValType, class Counter>
const ValType& SharedPtr<ValType, Counter>::operator*() const {
  return *m_ptr;
}

template<class ValType, class Counter>
ValType& SharedPtr<ValType, Counter>::operator*() {
  return *m_ptr;
}

template<class ValType, class Counter>
const ValType* SharedPtr<ValType, Counter>::operator->() const {
  return m_ptr;
}

template<class ValType, class Counter>
ValType* SharedPtr<ValType, Counter>::operator->() {
  return m_ptr;
}

template<class ValType, class Counter>
bool SharedPtr<ValType, Counter>::operator==(const SharedPtr& a_other) const {
  return m_ptr == a_other.m_ptr;
}

template<class ValType, class Counter>
template<class DerivedT, class CounterT>
SharedPtr<ValType, Counter>::SharedPtr(SharedPtr<DerivedT, CounterT> a_value)
: m_ptr (a_value.m_ptr)
, m_numOfInstances(a_value.m_numOfInstances) {
}



/* --------------- Private Functions --------------- */

template<class ValType, class Counter>
void SharedPtr<ValType, Counter>::remove() {
  if (1 == m_numOfInstances.Get()) {
    delete m_ptr;
  }
}

#endif // SharedPtr_INL