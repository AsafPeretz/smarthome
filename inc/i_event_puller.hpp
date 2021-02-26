#ifndef I_EVENT_PULLER_HPP
#define I_EVENT_PULLER_HPP

#include "shared_ptr.hpp"
#include "event.hpp"

namespace smarthome {

class IEventPuller {
public:
  // IEventPuller() = delete
  virtual ~IEventPuller();
  virtual void PopEvent(SharedPtr<Event>& a_retval) = 0;

}; // IEventPuller

} // smarthome

#endif // I_EVENT_PULLER_HPP