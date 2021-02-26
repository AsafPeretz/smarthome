#include "event_handle.hpp"
#include <iostream>

namespace smarthome {

extern std::string g_eventType;
extern std::string g_eventData;
extern std::string g_typeTest;
extern std::string g_dataTest;

EventHandle::EventHandle()
{
}

EventHandle::~EventHandle() {
}

void EventHandle::HandleEvent(const SharedPtr<Event>& a_event) {
  g_eventType = g_typeTest;
  g_eventData = g_dataTest;
}

IEventHandler::AgentId EventHandle::GetAgentId() const {
  return 1;
}

} // smarthome