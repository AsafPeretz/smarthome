#ifndef CONTROLLER_CREATOR_HPP
#define CONTROLLER_CREATOR_HPP

#include "i_agent_creator.hpp"
#include "shared_ptr.hpp"
#include "agent.hpp"
#include <vector>
#include <string>

namespace smarthome {

class ControllerCreator : public IAgentCreator<Agent> {
public:
  ControllerCreator(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~ControllerCreator();
  virtual SharedPtr<Agent> Create() const;
  virtual std::string GetName() const;
  
private:
  SharedPtr<AgentAdapter> m_adapter;
  std::vector<std::string> m_subs;
};  // ControllerCreator

}  // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::AgentAdapter>& a_adapter);

}

#endif // CONTROLLER_CREATOR_HPP