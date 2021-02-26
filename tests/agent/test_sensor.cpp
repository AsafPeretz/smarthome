#include "i_event_populator.hpp"
#include "i_event_pool.hpp"
#include "event_queue.hpp"
#include "time_stamp.hpp"
#include "shared_ptr.hpp"
#include "location.hpp"
#include "logger.hpp"
#include "sensor.hpp"
#include "event.hpp"
#include "agent.hpp"
#include <iostream>

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

namespace smarthome {
smarthome::Logger g_logger;
}

static bool ComapreEvents(const smarthome::Event& a_event1, const smarthome::Event& a_event2);
static bool Test_push_from_agent(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_push_from_agent, testName)
}

static bool Test_push_from_agent(std::string& a_testName) {
  a_testName = "Test_push_from_agent";
  smarthome::SharedPtr<smarthome::IEventPool> eventQueue(new smarthome::EventQueue);
  smarthome::Sensor sensor(eventQueue);
  sensor.Start();

  smarthome::SharedPtr<smarthome::Event> eventFromPool(new smarthome::Event());
  eventQueue->PopEvent(eventFromPool);

  smarthome::Event newEvent("TypeA", smarthome::EventTimeStamp("05.05.2020" ,"22:05:01"), "temp: +0.2", smarthome::EventLocation("Landing", "Lobby"));
  if (ComapreEvents(*eventFromPool, newEvent) != true) {
    return false;
  }
  return true;
}



/*  --------------- Local Functions --------------- */

static bool ComapreEvents(const smarthome::Event& a_event1, const smarthome::Event& a_event2) {
  if (a_event1.GetType() != a_event2.GetType()) {
    return false;
  }
  if (a_event1.GetTime().GetDate() != a_event2.GetTime().GetDate()) {
    return false;
  }
  if (a_event1.GetTime().GetTime() != a_event2.GetTime().GetTime()) {
    return false;
  }
  if (a_event1.GetData() != a_event2.GetData()) {
    return false;
  }
  if (a_event1.GetLocation() != a_event2.GetLocation()) {
    return false;
  }
  return true;
}
