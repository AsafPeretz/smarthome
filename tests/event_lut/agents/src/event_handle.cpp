#include "event_handle.hpp"
#include <iostream>

namespace smarthome {

EventHandle::EventHandle()
{
}

EventHandle::~EventHandle() {
}

void EventHandle::HandleEvent(const SharedPtr<Event>& a_event) {
  std::cout << "Type: " << a_event->GetType() << " | ";
  std::cout << "Date: " << a_event->GetTime().GetDate() << " | ";
  std::cout << "Time: " << a_event->GetTime().GetTime() << " | ";
  std::cout << "Data: " << a_event->GetData() << " | " << std::endl;
  std::cout << a_event->GetLocation().GetFloor() << " | ";
  std::cout << a_event->GetLocation().GetRoom() << " | " << std::endl;
  std::cout << std::endl;
}

IEventHandler::AgentId EventHandle::GetAgentId() const {
  return 1;
}

} // smarthome