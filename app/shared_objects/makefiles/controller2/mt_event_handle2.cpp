 #include "mt_event_handle2.hpp"
#include <iostream>
#include <climits>

namespace smarthome {

MTEventHandle2::MTEventHandle2(const AgentId& a_id)
: m_id(a_id)
{
}

MTEventHandle2::~MTEventHandle2() {
}

void MTEventHandle2::HandleEvent(const SharedPtr<Event>& a_event) {
  std::cout << "Start Handle Controller2" << std::endl;
  std::cout << "Type: " << a_event->GetType() << " | ";
  std::cout << "Date: " << a_event->GetTime().GetDate() << " | ";
  std::cout << "Time: " << a_event->GetTime().GetTime() << " | ";
  std::cout << "Data: " << a_event->GetData() << " | " << std::endl;
  std::cout << a_event->GetLocation().GetFloor() << " | ";
  std::cout << a_event->GetLocation().GetRoom() << " | " << std::endl;
  std::cout << std::endl;
  for (int i = 1 ; i != 1000000000 ; ++i) {
  }
  std::cout << "End Handle Controller2" << std::endl;
}

AgentId MTEventHandle2::GetAgentId() const {
  return m_id;
}

} // smarthome