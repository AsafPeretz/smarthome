#include "i_event_handler.hpp"
#include "event_handle.hpp"
#include "distributer.hpp"
#include "shared_ptr.hpp"
#include "time_stamp.hpp"
#include "location.hpp"
#include "event.hpp"
#include <iostream>
#include <string>

namespace smarthome {
std::string g_eventType;
std::string g_eventData;
std::string g_typeTest = "TypeTest";
std::string g_dataTest = "DataTest";
}

static bool Test_one_event_mvp(std::string& a_testName);

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

int main() {
  std::string testName;
  PRINT_TEST(Test_one_event_mvp, testName)
}

static bool Test_one_event_mvp(std::string& a_testName) {
  a_testName = "Test_one_event_mvp";
  smarthome::SharedPtr<smarthome::IEventHandler> handler(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::Event> e1(new smarthome::Event("TypeA", smarthome::EventTimeStamp("05.05.2020", "23:36:01"), "DataA", smarthome::EventLocation("Floor4", "Room2")));
  smarthome::Distributer dist;
  dist.Distribute(e1, handler);
  if (smarthome::g_eventType != smarthome::g_typeTest || smarthome::g_eventData != smarthome::g_dataTest) {
    return false;
  }
  return true;
}
