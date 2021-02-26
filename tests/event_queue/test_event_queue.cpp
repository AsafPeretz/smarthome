#include "i_event_pool.hpp"
#include "event_queue.hpp"
#include "time_stamp.hpp"
#include "logger.hpp"
#include <iostream>

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_size(std::string& a_testName);
static bool Test_push_and_pull(std::string& a_testName);

static bool ComapreEvents(const smarthome::Event& a_event1, const smarthome::Event& a_event2);

namespace smarthome {
smarthome::Logger g_logger;
}

int main() {
  std::string testName;
  PRINT_TEST(Test_size, testName)
  PRINT_TEST(Test_push_and_pull, testName)
}

static bool Test_size(std::string& a_testName) {
  a_testName = "Test_size";
  smarthome::SharedPtr<smarthome::Event> event1(new smarthome::Event("typeA" , smarthome::EventTimeStamp("05.05.2020", "23:05:58"), "smoke", smarthome::EventLocation("3", "112B")));
  smarthome::SharedPtr<smarthome::Event> event2(new smarthome::Event("typeB" , smarthome::EventTimeStamp("05.05.2020", "07:33:42"), "movement", smarthome::EventLocation("1", "8")));
  smarthome::SharedPtr<smarthome::Event> event3(new smarthome::Event("typeB" , smarthome::EventTimeStamp("05.05.2020", "07:41:42"), "movement", smarthome::EventLocation("1", "8")));
  smarthome::EventQueue eventPool;
  if (eventPool.Size() != 0) {
    return false;
  }
  eventPool.PushEvent(event1);
  eventPool.PushEvent(event2);
  eventPool.PushEvent(event3);
  if (eventPool.Size() != 3) {
    return false;
  }
  smarthome::SharedPtr<smarthome::Event> buffer(NULL);
  eventPool.PopEvent(buffer);
  if (eventPool.Size() != 2) {
    return false;
  }
  eventPool.PopEvent(buffer);
  if (eventPool.Size() != 1) {
    return false;
  }
  eventPool.PopEvent(buffer);
  if (eventPool.Size() != 0) {
    return false;
  }
  return true;
}


static bool Test_push_and_pull(std::string& a_testName) {
  a_testName = "Test_push_and_pull";
  smarthome::SharedPtr<smarthome::Event> event1(new smarthome::Event("typeA" , smarthome::EventTimeStamp("05.05.2020", "23:05:58"), "smoke", smarthome::EventLocation("3", "112B")));
  smarthome::SharedPtr<smarthome::Event> event2(new smarthome::Event("typeB" , smarthome::EventTimeStamp("05.05.2020", "07:33:42"), "movement", smarthome::EventLocation("1", "8")));
  smarthome::SharedPtr<smarthome::Event> event3(new smarthome::Event("typeB" , smarthome::EventTimeStamp("05.05.2020", "07:41:42"), "movement", smarthome::EventLocation("1", "8")));
  smarthome::EventQueue eventPool;
  eventPool.PushEvent(event1);
  eventPool.PushEvent(event2);
  eventPool.PushEvent(event3);
  smarthome::SharedPtr<smarthome::Event> buffer(new smarthome::Event);
  eventPool.PopEvent(buffer);
  if (!ComapreEvents(*event1, *buffer)) {
    return false;
  }
  eventPool.PopEvent(buffer);
  if (!ComapreEvents(*event2, *buffer)) {
    return false;
  }
  eventPool.PopEvent(buffer);
  if (!ComapreEvents(*event3, *buffer)) {
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
