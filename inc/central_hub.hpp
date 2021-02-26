#ifndef CENTRAL_HUB_HPP
#define CENTRAL_HUB_HPP

#include "distribution_manager.hpp"
#include "i_agent_factory.hpp"
#include "i_event_pool.hpp"
#include "i_lut_finder.hpp"
#include "i_event_lut.hpp"
#include "file_reader.hpp"
#include "event_queue.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"
#include "logger.hpp"
#include "agent.hpp"
#include <vector>

namespace smarthome {

class CentralHub : private UnCopyable {
public:
  explicit CentralHub(const std::string& a_filePath, const std::string& a_libPath, const std::string& a_funcName);
  ~CentralHub();
  void Start();

public:
  typedef std::vector<smarthome::SharedPtr<smarthome::Agent> > AgentContainer;

private:
  void createAgentFromFile();

private:
  SharedPtr<IAgentFactory> m_factory;
  SharedPtr<IEventPool> m_eventQueue;
  SharedPtr<IEventLut> m_eventLut;
  AgentContainer m_agents;
  DistManager m_dist;
  FileReader m_fileReader;
}; // CentralHub

}  // smarthome

#endif // CENTRAL_HUB_HPP