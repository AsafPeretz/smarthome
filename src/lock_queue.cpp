#include "./lock_queue.hpp"

namespace smarthome {

LockQueue::LockQueue()
: m_que()
, m_isActive(false)
{
}

void LockQueue::Enqueue(const HandlerPair& a_event) {
  m_que.Enqueue(a_event);
}

void LockQueue::Dequeue(HandlerPair& a_retval) {
  m_que.Dequeue(a_retval);
}

bool LockQueue::Empty() const {
  return m_que.IsEmpty();
}

bool LockQueue::IsActive() const {
  return m_isActive.Get();
}

void LockQueue::SetActive() {
  m_isActive = true;
}

void LockQueue::SetNonActive() {
  m_isActive = false;
}

} // smarthome