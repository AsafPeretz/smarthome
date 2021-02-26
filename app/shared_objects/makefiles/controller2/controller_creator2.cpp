#include "controller_creator2.hpp"
#include "mt_controller2.hpp"

namespace smarthome {

ControllerCreator2::ControllerCreator2(const SharedPtr<AgentAdapter>& a_adapter)
: m_adapter(a_adapter)
{
}

ControllerCreator2::~ControllerCreator2() {
}

SharedPtr<Agent> ControllerCreator2::Create() const {
  SharedPtr<Agent> controller(new MTController2(m_adapter));
  return controller;
}

std::string ControllerCreator2::GetName() const {
  return "MTController2";
}

} // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::AgentAdapter>& a_adapter) {
  smarthome::IAgentCreator<smarthome::Agent>* creator = new smarthome::ControllerCreator2(a_adapter);
  return creator;
}

} // extern "C"
