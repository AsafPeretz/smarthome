#include "distribution_mediator.hpp"
#include "i_event_handler.hpp"
#include "event_handle.hpp"
#include "event_queue.hpp"
#include "time_stamp.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"
#include "location.hpp"
#include "logger.hpp"
#include "event.hpp"

namespace smarthome {
smarthome::Logger g_logger;
}

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_one_event_mvp(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_one_event_mvp, testName)
}

static bool Test_one_event_mvp(std::string& a_testName) {
  a_testName = "Test_one_event_mvp";
  smarthome::SharedPtr<smarthome::IEventPool> queue(new smarthome::EventQueue);
  smarthome::SharedPtr<smarthome::IEventHandler> temp(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> temp2(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> smoke(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> movement(new smarthome::EventHandle);

  smarthome::SharedPtr<smarthome::Event> e1(new smarthome::Event("temp", smarthome::EventTimeStamp("05.05.2020", "23:36:01"), "DataA", smarthome::EventLocation("Floor4", "Room2")));
  smarthome::SharedPtr<smarthome::Event> e2(new smarthome::Event("temp", smarthome::EventTimeStamp("05.05.2020", "02:59:59"), "HAVA", smarthome::EventLocation("Floor1", "Room2")));
  smarthome::SharedPtr<smarthome::Event> e3(new smarthome::Event("movement", smarthome::EventTimeStamp("05.05.2020", "14:11:12"), "AFI", smarthome::EventLocation("Floor1", "Room3")));
  smarthome::SharedPtr<smarthome::Event> e4(new smarthome::Event("fire", smarthome::EventTimeStamp("05.05.2020", "16:32:21"), "EVE", smarthome::EventLocation("Floor3", "Room3")));

  queue->PushEvent(e1);
  queue->PushEvent(e2);
  queue->PushEvent(e3);
  queue->PushEvent(e4);

  smarthome::SharedPtr<smarthome::IEventLut> lut(new smarthome::EventLut);
  smarthome::EventDetails d1(smarthome::Type("temp"));
  lut->Register(temp, d1);
  smarthome::EventDetails d2(smarthome::Type("temp"));
  lut->Register(temp2, d2);
  smarthome::EventDetails d3(smarthome::Type("smoke"));
  lut->Register(smoke, d3);
  smarthome::EventDetails d4(smarthome::Type("movement"));
  lut->Register(movement, d4);

  smarthome::DistributionMediator mediator(queue, lut);
  smarthome::IEventLut::Handlers h1;
  size_t h_sizes[] = { 2, 2, 1, 0 }, queueSize = queue->Size(), j = 0;
  while (0 != queue->Size()) {
    smarthome::SharedPtr<smarthome::Event> eventPtr = mediator.Mediate(h1);
    if (h1.size() != h_sizes[j++] || --queueSize != queue->Size()) {
      return false;
    }
    for (size_t i = 0 ; i < h1.size() ; ++i) {
      h1[i]->HandleEvent(eventPtr);
    }
  }
  return true;
}
