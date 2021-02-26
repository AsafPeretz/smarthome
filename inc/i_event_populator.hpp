#ifndef I_EVENT_POPULATOR_HPP
#define I_EVENT_POPULATOR_HPP

#include "shared_ptr.hpp"
#include "event.hpp"

namespace smarthome {

class IEventPopulator {
public:
  // IEventPopulator() = delete
  virtual ~IEventPopulator();
  virtual void PushEvent(SharedPtr<Event> a_event) = 0;

}; // IEventPopulator

} // smarthome

#endif // I_EVENT_POPULATOR_HPP