#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include "cond_var.hpp"
#include "mutex.hpp"
#include "guard_mutex.hpp"
#include "atomic_value.hpp"
#include <queue>
#include <utility>

namespace smarthome {

class CondVarFunc;
#include "./inl/thread_safe_queue_condfunc.inl"

template<class ValType>
class ThreadSafeQueue : private UnCopyable {
public:
  explicit ThreadSafeQueue(size_t a_capacity = ~0);
  ~ThreadSafeQueue();
  bool Enqueue(const ValType& a_element);
  bool Dequeue(ValType& a_item);
  size_t Size() const;
  bool IsEmpty() const;
  bool IsFull() const;
  void Clear();
  
  #ifdef QUEUE_DEBUG
  bool Dequeue(std::pair<ValType, size_t>& a_item);
  #endif // QUEUE_DEBUG

private:
  void releaseWaiters();
  void popAllElements();
  void shutDown();
  void removeWaitersAndWait();

private:
  std::queue<ValType> m_elements;
  AtomicValue<size_t> m_numOfElements;
  size_t m_capacity;
  AtomicValue<size_t> m_enqueWaiters;
  AtomicValue<size_t> m_dequeWaiters;
  CondVar m_notEmpty;
  CondVar m_notFull;
  CondVar m_shutdownEnq;
  CondVar m_shutdownDeq;
  mutable Mutex m_queueMutex;
  AtomicValue<bool> m_stop;

}; // ThreadSafeQueue

#include "./inl/thread_safe_queue.inl"

}  // smarthome

#endif // THREAD_SAFE_QUEUE_HPP