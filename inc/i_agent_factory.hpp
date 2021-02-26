#ifndef I_AGENT_FACTORY_HPP
#define I_AGENT_FACTORY_HPP

#include "agent_adapter.hpp"
#include "shared_ptr.hpp"
#include "uncopyable.hpp"
#include "agent.hpp"
#include <string>

namespace smarthome {

class IAgentFactory : private UnCopyable {
public:
  virtual ~IAgentFactory();
  virtual void InsertAdapter(const SharedPtr<AgentAdapter>& a_adapter) = 0;
  virtual SharedPtr<Agent> Create(const std::string& a_AgentName) = 0;
}; // IAgentFactory

}  // smarthome

#endif // I_AGENT_FACTORY_HPP