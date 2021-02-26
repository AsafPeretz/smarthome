#ifndef THREAD_SAFE_QUEUE_INL
#define THREAD_SAFE_QUEUE_INL

class CondVarDtor;
#include "cond_var_dtor.inl"

template<class ValType>
ThreadSafeQueue<ValType>::ThreadSafeQueue(size_t a_capacity)
: m_elements()
, m_numOfElements(0)
, m_capacity(a_capacity)
, m_enqueWaiters(0)
, m_dequeWaiters(0)
, m_notEmpty()
, m_notFull()
, m_queueMutex()
, m_stop(false) {
}

template<class ValType>
ThreadSafeQueue<ValType>::~ThreadSafeQueue() {
  GuardMutex dtorGuard(m_queueMutex);
  removeWaitersAndWait();
}

template<class ValType>
bool ThreadSafeQueue<ValType>::Enqueue(const ValType& a_element) {
  if (m_stop.Get()) {
    return false;
  }
  { // GuardMutex
    GuardMutex enqueueGuard(m_queueMutex);
    ++m_enqueWaiters;
    m_notFull.Wait<CondVarFunc>(m_queueMutex, CondVarFunc(m_numOfElements, m_capacity, m_stop));
    --m_enqueWaiters;
    if (m_stop.Get()) {
      if (m_enqueWaiters.Compare(0)) {
        m_shutdownEnq.Signal();
      }
      return false;
    }
    m_elements.push(a_element);
    ++m_numOfElements;
  }
  if (!m_dequeWaiters.Compare(0)) {
    m_notEmpty.Signal();
  }
  return true;
}

template<class ValType>
bool ThreadSafeQueue<ValType>::Dequeue(ValType& a_item) {
  if (m_stop.Get()) {
    return false;
  }
  { // GuardMutex
    GuardMutex enqueueGuard(m_queueMutex);
    ++m_dequeWaiters;
    m_notEmpty.Wait<CondVarFunc>(m_queueMutex, CondVarFunc(m_numOfElements, 0,  m_stop));
    --m_dequeWaiters;
    if (m_stop.Get()) {
      if (m_dequeWaiters.Compare(0)) {
        m_shutdownDeq.Signal();
      }
      return false;
    }
    a_item = m_elements.front();
    m_elements.pop();
    --m_numOfElements;
  }
  if (!m_enqueWaiters.Compare(0)) {
    m_notEmpty.Signal();
  }
  return true;
}

template<class ValType>
size_t ThreadSafeQueue<ValType>::Size() const {
  GuardMutex sizeGuard(m_queueMutex);
  return m_elements.size();
}

template<class ValType>
bool ThreadSafeQueue<ValType>::IsEmpty() const {
  GuardMutex isEmptyGuard(m_queueMutex);
  return m_numOfElements.Compare(0);
}

template<class ValType>
bool ThreadSafeQueue<ValType>::IsFull() const {
  GuardMutex isFullGuard(m_queueMutex);
  return m_numOfElements.Compare(m_capacity);
}

template<class ValType>
void ThreadSafeQueue<ValType>::Clear() {
  GuardMutex clearGuard(m_queueMutex);
  removeWaitersAndWait();
  popAllElements();
  m_stop = false;  
}

#ifdef QUEUE_DEBUG
template<class ValType>
bool ThreadSafeQueue<ValType>::Dequeue(std::pair<ValType, size_t>& a_item) {
  if (m_stop.Get()) {
    return false;
  }
  { // GuardMutex
    GuardMutex enqueueGuard(m_queueMutex);
    ++m_dequeWaiters;
    m_notEmpty.Wait<CondVarFunc>(m_queueMutex, CondVarFunc(m_numOfElements, 0,  m_stop));
    --m_dequeWaiters;
    if (m_stop.Get()) {
      if (m_dequeWaiters.Compare(0)) {
        m_shutdownDeq.Signal();
      }
      return false;
    }
    a_item.first = m_elements.front();
    clock_t clock1 = clock();
    a_item.second = clock1;
    m_elements.pop();
    --m_numOfElements;
  }
  if (!m_enqueWaiters.Compare(0)) {
    m_notEmpty.Signal();
  }
  return true;
}
#endif // QUEUE_DEBUG



/* --------------- Private Functions --------------- */

template<class ValType>
void ThreadSafeQueue<ValType>::popAllElements() {
  while (0 != m_elements.size()) {
    m_elements.pop();
  }
  m_numOfElements = 0;
}

template<class ValType>
void ThreadSafeQueue<ValType>::releaseWaiters() {
  m_stop = true;
  m_notFull.BroadCast();
  m_notEmpty.BroadCast();
}

template<class ValType>
void ThreadSafeQueue<ValType>::removeWaitersAndWait() {
  releaseWaiters();
  m_shutdownEnq.Wait<CondVarDtor>(m_queueMutex, CondVarDtor(m_enqueWaiters, 0));
  m_shutdownDeq.Wait<CondVarDtor>(m_queueMutex, CondVarDtor(m_dequeWaiters, 0));
}

#endif // THREAD_SAFE_QUEUE_INL