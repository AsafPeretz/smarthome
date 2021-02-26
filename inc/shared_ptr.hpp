#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include "atomic_counter.hpp"

namespace smarthome {

template<class ValType, class Counter = AtomicCounter>
class SharedPtr {
public:
  explicit SharedPtr(ValType* a_value);
  SharedPtr(const SharedPtr& a_other);
  ~SharedPtr();
  SharedPtr& operator=(const SharedPtr& a_other);
  ValType& operator*();
  const ValType& operator*() const;
  ValType* operator->();
  const ValType* operator->() const;
  bool operator==(const SharedPtr& a_other) const;
  
  template<class DerivedT, class CounterT> friend class SharedPtr;
  template<class DerivedT, class CounterT>SharedPtr(SharedPtr<DerivedT, CounterT> a_value);
  
private:
  void remove();

private:
  ValType* m_ptr;
  Counter m_numOfInstances;
}; // SHAREDPTR_HPP

#include "./inl/shared_ptr.inl"

}  // smarthome

#endif // SharedPtr_HPP