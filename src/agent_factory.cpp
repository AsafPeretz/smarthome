#include "agent_factory.hpp"
#include <iostream>
#include "logger.hpp"

namespace smarthome {

extern Logger g_logger;

AgentFactory::AgentFactory(const std::string& a_libPath, const std::string& a_funcName)
: m_dl()
, m_factory()
{
  smarthome::Dirent dirent(a_libPath);
  std::string libName;
  while(dirent.GetNextFilePath(libName))  {
    m_dl.push_back(smarthome::SharedPtr<smarthome::DlLib>(new smarthome::DlLib(libName, a_funcName)));
  }  
}

AgentFactory::~AgentFactory() {
}


void AgentFactory::InsertAdapter(const SharedPtr<AgentAdapter>& a_adapter) {
  for (size_t i = 0 ; i < m_dl.size() ; ++i) {
    smarthome::FunctionPtr func = m_dl[i]->GetFunction();
    smarthome::SharedPtr<smarthome::IAgentCreator<smarthome::Agent> > agentCreator(static_cast<smarthome::IAgentCreator<smarthome::Agent>* >(func(a_adapter)));
    m_factory.Register(agentCreator->GetName(), agentCreator);
  }
}


SharedPtr<Agent> AgentFactory::Create(const std::string& a_AgentName) {
  SharedPtr<Agent> retval = m_factory.Create(a_AgentName);
  g_logger << "agent created, id = " << retval->GetId() << std::endl;
  return retval;
}


} // smarthome