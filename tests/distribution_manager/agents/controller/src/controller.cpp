#include "controller.hpp"
#include <iostream>

namespace smarthome {

size_t MTController::m_idPool = 0;

MTController::MTController(const SharedPtr<AgentAdapter>& a_adapter)
: IController(a_adapter)
, m_id(++m_idPool)
, m_handle(new MTEventHandle(m_id))
, m_subManager(this->GetSubManager())
, m_subs()
{
  EventDetails temp("temp");
  m_subs.push_back(temp);
}

MTController::~MTController() {
}

void MTController::Start() {
}

void MTController::Subscribe() { 
  for (size_t i = 0 ; i < m_subs.size() ; ++i) {
    m_subManager->Register(m_handle, m_subs[i]);
  }
}

AgentId MTController::GetId() const {
  return m_id;
}

} // smarthome
