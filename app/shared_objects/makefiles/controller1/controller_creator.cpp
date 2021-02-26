#include "controller_creator.hpp"
#include "mt_controller.hpp"

namespace smarthome {

ControllerCreator::ControllerCreator(const SharedPtr<AgentAdapter>& a_adapter)
: m_adapter(a_adapter)
{
}

ControllerCreator::~ControllerCreator() {
}

SharedPtr<Agent> ControllerCreator::Create() const {
  SharedPtr<Agent> controller(new MTController(m_adapter));
  return controller;
}

std::string ControllerCreator::GetName() const {
  return "MTController";
}

} // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::AgentAdapter>& a_adapter) {
  smarthome::IAgentCreator<smarthome::Agent>* creator = new smarthome::ControllerCreator(a_adapter);
  return creator;
}

} // extern "C"
