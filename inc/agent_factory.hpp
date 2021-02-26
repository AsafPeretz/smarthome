#ifndef AGENT_FACTORY_HPP
#define AGENT_FACTORY_HPP

#include "i_agent_factory.hpp"
#include "i_agent_creator.hpp"
#include "agent_adapter.hpp"
#include "shared_ptr.hpp"
#include "uncopyable.hpp"
#include "factory.hpp"
#include "dirent.hpp"
#include "dl_lib.hpp"
#include "agent.hpp"
#include <string>
#include <vector>

namespace smarthome {

class AgentFactory : public IAgentFactory {
public:
  AgentFactory(const std::string& a_libPath, const std::string& a_funcName);
  virtual ~AgentFactory();
  virtual void InsertAdapter(const SharedPtr<AgentAdapter>& a_adapter);
  virtual SharedPtr<Agent> Create(const std::string& a_AgentName);

private:
  std::vector<SharedPtr<DlLib> > m_dl;
  Factory<std::string, Agent> m_factory;
}; // AgentFactory

}  // smarthome

#endif // AGENT_FACTORY_HPP