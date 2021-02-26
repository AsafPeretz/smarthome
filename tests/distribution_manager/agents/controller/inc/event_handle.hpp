#ifndef MT_EVENT_HANDLE_HPP
#define MT_EVENT_HANDLE_HPP

#include "i_event_handler.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"
#include "agent.hpp"

namespace smarthome {

class MTEventHandle : public IEventHandler {
public:
  explicit MTEventHandle(const AgentId& a_id);
  virtual ~MTEventHandle();
  virtual void HandleEvent(const SharedPtr<Event>& a_event);
  virtual AgentId GetAgentId() const;

private:
  AgentId m_id;
}; // MTEventHandle

} // smarthome

#endif // MT_EVENT_HANDLE_HPP