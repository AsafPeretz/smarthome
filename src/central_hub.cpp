#include "i_event_populator.hpp"
#include "i_sub_manager.hpp"
#include "agent_factory.hpp"
#include "agent_adapter.hpp"
#include "central_hub.hpp"
#include "thread.hpp"
#include "routine.hpp"
#include "logger.hpp"
#include <iostream>
#include <algorithm>
#include <time.h>

namespace smarthome {

Logger g_logger;

class StartAgents {
public:
  void operator()(SharedPtr<smarthome::Agent>& a_agent) {
    a_agent->Start();
  }
}; // StartAgents


class DistRoutine : public Routine {
public:
  DistRoutine(CentralHub::AgentContainer& a_agents, DistManager& a_dist)
  : m_agents(a_agents)
  , m_dist(a_dist)
  {
  }
  virtual ~DistRoutine() {}
  virtual void Do() {
    m_dist.Run(m_agents);
  }

private:
  CentralHub::AgentContainer& m_agents;
  DistManager& m_dist;
}; // DistRoutine



// CentralHub

CentralHub::CentralHub(const std::string& a_filePath, const std::string& a_libPath, const std::string& a_funcName)
: m_factory(new AgentFactory(a_libPath, a_funcName))
, m_eventQueue(new EventQueue)
, m_eventLut(new EventLut)
, m_agents()
, m_dist(m_eventQueue, m_eventLut)
, m_fileReader(a_filePath)
{
  g_logger << "Central hub constructed" << std::endl;
  time_t now = time(0);
  tm* localTime = localtime(&now);
  g_logger << asctime(localTime) << std::endl << std::endl;

  SharedPtr<AgentAdapter> adapter(new AgentAdapter(m_eventLut, m_eventQueue));
  m_factory->InsertAdapter(adapter);
  createAgentFromFile();
}

CentralHub::~CentralHub() {
  g_logger << "\n" << "Central hub destructed" << std::endl << std::endl;
  time_t now = time(0);
  tm* localTime = localtime(&now);
  g_logger << asctime(localTime) << std::endl << std::endl;
}

void CentralHub::Start() {
  std::cout << "Write \"stop\" to close the app" << std::endl << std::endl;
  std::for_each(m_agents.begin(), m_agents.end(), StartAgents());

  SharedPtr<Routine> rout(new DistRoutine(m_agents, m_dist));
  Thread t1(rout);

  std::string stop;
  while (stop.compare("stop") != 0) {
    std::cin >> stop;
    if (stop.compare("stop") == 0) {
      m_dist.Pause();
      m_eventQueue->PushEvent(SharedPtr<Event>(new Event()));
    }
  }
  t1.Join();
}


void CentralHub::createAgentFromFile() {
  while (m_fileReader.IsValid()) {
    std::string agentName = m_fileReader.GetNextLine();
    SharedPtr<Agent> agent = m_factory->Create(agentName);
    agent->Subscribe();
    m_agents.push_back(agent);
  }
}

} // smarthome