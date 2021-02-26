#ifndef MT_EVENT_HANDLE_TWO_HPP
#define MT_EVENT_HANDLE_TWO_HPP

#include "i_event_handler.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"
#include "agent.hpp"

namespace smarthome {

class MTEventHandle2 : public IEventHandler {
public:
  explicit MTEventHandle2(const AgentId& a_id);
  virtual ~MTEventHandle2();
  virtual void HandleEvent(const SharedPtr<Event>& a_event);
  virtual AgentId GetAgentId() const;

private:
  AgentId m_id;
}; // MTEventHandle2

} // smarthome

#endif // MT_EVENT_HANDLE_HPP