#ifndef LOCK_QUEUE_HPP
#define LOCK_QUEUE_HPP

#include "thread_safe_queue.hpp"
#include "i_event_handler.hpp"
#include "atomic_value.hpp"
#include "shared_ptr.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include <utility>

namespace smarthome {
  
class LockQueue {
typedef std::pair<Event, SharedPtr<IEventHandler> > HandlerPair;
typedef ThreadSafeQueue<HandlerPair> TSQueue;

public:
  LockQueue();
  // ~LockQueue() = default
  void Enqueue(const HandlerPair& a_event);
  void Dequeue(HandlerPair& a_handler);
  bool Empty() const;
  bool IsActive() const;
  void SetActive();
  void SetNonActive();

private:
  TSQueue m_que;
  AtomicValue<bool> m_isActive;

}; // LockQueue

}  // smarthome

#endif // LOCK_QUEUE_HPP