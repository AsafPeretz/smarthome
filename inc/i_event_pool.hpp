#ifndef EVENT_POOL_HPP
#define EVENT_POOL_HPP

#include "i_event_populator.hpp"
#include "i_event_puller.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"

namespace smarthome {

class IEventPool : public IEventPopulator, public IEventPuller {
public:
  // IEventPool() = delete
  virtual ~IEventPool();
  virtual size_t Size() const = 0;
  virtual void PushEvent(SharedPtr<Event> a_event) = 0;
  virtual void PopEvent(SharedPtr<Event>& a_retval) = 0;

}; // IEventPool

}  // smarthome

#endif // EVENT_POOL_HPP