#include "i_controller.hpp"

namespace smarthome {

IController::IController(const SharedPtr<AgentAdapter>& a_adapter)
: m_subs()
, m_adapter(a_adapter)
{
}

IController::~IController() {
}


SharedPtr<ISubManager> IController::GetSubManager() {
  return m_adapter->m_subManager;
}

} // smarthome