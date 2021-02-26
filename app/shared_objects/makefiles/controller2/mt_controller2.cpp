#include "mt_controller2.hpp"
#include <iostream>

namespace smarthome {

size_t MTController2::m_idPool = 100;

MTController2::MTController2(const SharedPtr<AgentAdapter>& a_adapter)
: IController(a_adapter)
, m_id(++m_idPool)
, m_handle(new MTEventHandle2(m_id))
, m_subManager(this->GetSubManager())
, m_subs()
{
  EventDetails smoke("smoke");
  m_subs.push_back(smoke);
}

MTController2::~MTController2() {
}

void MTController2::Start() {
}

void MTController2::Subscribe() { 
  for (size_t i = 0 ; i < m_subs.size() ; ++i) {
    m_subManager->Register(m_handle, m_subs[i]);
  }
}

AgentId MTController2::GetId() const {
  return m_id;
}

} // smarthome
