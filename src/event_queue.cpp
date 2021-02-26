#include "event_queue.hpp"
#include "logger.hpp"

namespace smarthome {

extern Logger g_logger;

EventQueue::EventQueue(size_t a_capacity)
: m_events(a_capacity)
{
}

EventQueue::~EventQueue() {
}

void EventQueue::PopEvent(SharedPtr<Event>& a_retval) {
  m_events.Dequeue(a_retval);
  g_logger << "Event of type " << a_retval->GetType() << " was pulled to event pool." << std::endl;
}

void EventQueue::PushEvent(SharedPtr<Event> a_event) {
  m_events.Enqueue(a_event);
  g_logger << "Event of type " << a_event->GetType() << " was pushed to event pool." << std::endl;
}

size_t EventQueue::Size() const {
  return m_events.Size();
}

} // smarthome