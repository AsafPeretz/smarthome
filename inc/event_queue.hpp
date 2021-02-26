#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "thread_safe_queue.hpp"
#include "i_event_pool.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"


namespace smarthome {

class EventQueue : public IEventPool {
public:
  explicit EventQueue(size_t a_capacity = ~0);
  virtual ~EventQueue();
  virtual void PushEvent(SharedPtr<Event> a_event);
  virtual void PopEvent(SharedPtr<Event>& a_retval);
  virtual size_t Size() const;

private:
  ThreadSafeQueue<SharedPtr<Event> > m_events;
}; // EventQueue

}  // smarthome

#endif // EVENT_QUEUE_HPP