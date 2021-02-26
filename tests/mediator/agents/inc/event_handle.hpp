#ifndef EVENT_HANDLE_HPP
#define EVENT_HANDLE_HPP

#include "i_event_handler.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"

namespace smarthome {

class EventHandle : public IEventHandler {
public:
  explicit EventHandle();
  virtual ~EventHandle();
  virtual void HandleEvent(const SharedPtr<Event>& a_event);
  virtual IEventHandler::AgentId GetAgentId() const;

}; // EventHandle

} // smarthome

#endif // EVENT_HANDLE_HPP