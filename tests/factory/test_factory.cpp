#include "i_event_populator.hpp"
#include "i_agent_creator.hpp"
#include "i_sub_manager.hpp"
#include "agent_adapter.hpp"
#include "i_event_pool.hpp"
#include "event_queue.hpp"
#include "i_event_lut.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"
#include "factory.hpp"
#include "logger.hpp"
#include "dirent.hpp"
#include "dl_lib.hpp"
#include "agent.hpp"
#include "event.hpp"
#include <iostream>
#include <string>
#include <vector>

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_agent_create(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_agent_create, testName)
}

static bool Test_agent_create(std::string& a_testName) {
  a_testName = "Test_agent_create";
  smarthome::Dirent dirent("./sensor/so/");
  std::string libName;
  const std::string funcName = "MakeCreator";

  smarthome::SharedPtr<smarthome::IEventPool> que(new smarthome::EventQueue);
  smarthome::SharedPtr<smarthome::IEventLut> lut(new smarthome::EventLut);

  smarthome::SharedPtr<smarthome::AgentAdapter> adapter(new smarthome::AgentAdapter(lut, que));
 
  std::vector<smarthome::SharedPtr<smarthome::DlLib> > dlVec;
  smarthome::Factory<std::string, smarthome::Agent> factory;
  
  while(dirent.GetNextFilePath(libName))  {
    smarthome::SharedPtr<smarthome::DlLib> dl(new smarthome::DlLib(libName, funcName));
    dlVec.push_back(dl);
    smarthome::FunctionPtr func = dl->GetFunction();
    smarthome::SharedPtr<smarthome::IAgentCreator<smarthome::Agent> > agentCreator(static_cast<smarthome::IAgentCreator<smarthome::Agent>* >(func(adapter)));
    smarthome::SharedPtr<smarthome::Agent> agent = agentCreator->Create();
    agent->Start();
    factory.Register("defSensor", agentCreator);
    smarthome::SharedPtr<smarthome::Agent> agent2 = factory.Create("defSensor");
    agent2->Start();
    }
  return true;
}
