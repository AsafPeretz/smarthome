#include "distribution_mediator.hpp"
#include "distribution_manager.hpp"
#include "i_event_handler.hpp"
#include "agent_adapter.hpp"
#include "i_sub_manager.hpp"
#include "i_distributer.hpp"
#include "agent_factory.hpp"
#include "event_details.hpp"
#include "i_lut_finder.hpp"
#include "i_controller.hpp"
#include "event_queue.hpp"
#include "i_event_lut.hpp"
#include "distributer.hpp"
#include "rendezvous.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"
#include "i_sensor.hpp"
#include "location.hpp"
#include "factory.hpp"
#include "dirent.hpp"
#include "dl_lib.hpp"
#include "logger.hpp"
#include "agent.hpp"
#include "event.hpp"
#include "routine.hpp"
#include "thread.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>

namespace smarthome {
Logger g_logger;
}

class DistManagerRunRoutine : public smarthome::Routine {
public:
  DistManagerRunRoutine(smarthome::DistManager& a_distManager, std::vector<smarthome::SharedPtr<smarthome::Agent> >& a_agents)
  : m_dist(a_distManager)
  , m_agents(a_agents)
  {
  }
  virtual ~DistManagerRunRoutine() {}
  virtual void Do() {
    m_dist.Run(m_agents);
  }

private:
  smarthome::DistManager& m_dist;
  std::vector<smarthome::SharedPtr<smarthome::Agent> > m_agents;
}; // DistManagerRunRoutine


class DistManagerPauseRoutine : public smarthome::Routine {
public:
  DistManagerPauseRoutine(smarthome::DistManager& a_distManager, smarthome::SharedPtr<smarthome::IEventPool>& a_eventQueue)
  : m_dist(a_distManager)
  , m_eventQueue(a_eventQueue)
  {
  }
  virtual ~DistManagerPauseRoutine() {}
  virtual void Do() {
    m_dist.Pause();
    m_eventQueue->PushEvent(smarthome::SharedPtr<smarthome::Event>(new smarthome::Event()));
  }

private:
  smarthome::DistManager& m_dist;
  smarthome::SharedPtr<smarthome::IEventPool>& m_eventQueue;
}; // DistManagerPauseRoutine

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_distManager(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_distManager, testName)
}

static bool Test_distManager(std::string& a_testName) {
  a_testName = "Test_distManager";
  smarthome::AgentFactory factory("./so", "MakeCreator");
  smarthome::SharedPtr<smarthome::IEventPool> eventQueue(new smarthome::EventQueue);
  smarthome::SharedPtr<smarthome::IEventLut> lut(new smarthome::EventLut);
  smarthome::SharedPtr<smarthome::AgentAdapter> adapter(new smarthome::AgentAdapter(lut, eventQueue));
  factory.InsertAdapter(adapter);
  std::vector<smarthome::SharedPtr<smarthome::Agent> > agentVec;
  const size_t numOfSensors = 2;
  for (size_t i = 0 ; i < numOfSensors ; ++i) {
    smarthome::SharedPtr<smarthome::Agent> sensor = factory.Create("MTSensor");
    sensor->Subscribe();
    agentVec.push_back(sensor);
  }

  const size_t numOfControllers = 1;
  for (size_t i = 0 ; i < numOfControllers ; ++i) {
    smarthome::SharedPtr<smarthome::Agent> controller = factory.Create("MTController");
    controller->Subscribe();
    agentVec.push_back(controller);
  }

  for (size_t i = 0 ; i < agentVec.size() ; ++i) {
    agentVec[i]->Start();
  }

  smarthome::DistManager dist(eventQueue, lut);
  smarthome::SharedPtr<smarthome::Routine> routineRun(new DistManagerRunRoutine(dist, agentVec));
  smarthome::Thread threadRun(routineRun);

  sleep(2);

  smarthome::SharedPtr<smarthome::Routine> routinePause(new DistManagerPauseRoutine(dist, eventQueue));
  smarthome::Thread threadPause(routinePause);

  threadPause.Join();
  threadRun.Join();
  
  return true;
}
