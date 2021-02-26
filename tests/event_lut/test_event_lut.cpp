#include "i_event_handler.hpp"
#include "event_details.hpp"
#include "event_handle.hpp"
#include "i_event_lut.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_test_I(std::string& a_testName);
static bool Test_test_II(std::string& a_testName);
static bool Test_test_III(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_test_I, testName)
  PRINT_TEST(Test_test_II, testName)
  PRINT_TEST(Test_test_III, testName)
}


static bool Test_test_I(std::string& a_testName) {
  a_testName = "Test_test_I";
  smarthome::EventLut lut;
  smarthome::SharedPtr<smarthome::IEventHandler> temp(new smarthome::EventHandle);
  smarthome::EventDetails anyTemp(smarthome::Type("temp"), "Any", "Any");
  lut.Register(temp, anyTemp);
  smarthome::IEventLut::Handlers tempHandlers;
  smarthome::EventDetails temp51(smarthome::Type("temp"), "5", "1");
  lut.Find(temp51, tempHandlers);
  return (tempHandlers.size() == 1 ? true : false);
}

static bool Test_test_II(std::string& a_testName) {
  a_testName = "Test_test_II";
  smarthome::EventLut lut;
  smarthome::SharedPtr<smarthome::IEventHandler> temp(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> smoke(new smarthome::EventHandle);
  smarthome::EventDetails anyTemp(smarthome::Type("temp"), "Any", "Any");
  lut.Register(temp, anyTemp);
  smarthome::EventDetails roomSmoke(smarthome::Type("smoke"), "2", "3");
  lut.Register(smoke, roomSmoke);
  smarthome::IEventLut::Handlers tempHandlers;
  smarthome::EventDetails temp51(smarthome::Type("light"), "5", "1");
  lut.Find(temp51, tempHandlers);
  return (tempHandlers.size() == 0 ? true : false);
}

static bool Test_test_III(std::string& a_testName) {
  a_testName = "Test_test_III";
  smarthome::EventLut lut;
  smarthome::SharedPtr<smarthome::IEventHandler> temp(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> temp2(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> smoke(new smarthome::EventHandle);
  smarthome::SharedPtr<smarthome::IEventHandler> all(new smarthome::EventHandle);

  smarthome::EventDetails anyTemp(smarthome::Type("temp"), "Any", "Any");
  lut.Register(temp, anyTemp);
  smarthome::EventDetails floorTemp(smarthome::Type("temp"), "5", "Any");
  lut.Register(temp2, floorTemp);
  smarthome::EventDetails roomSmoke(smarthome::Type("smoke"), "2", "3");
  lut.Register(smoke, roomSmoke);
  smarthome::EventDetails allOfAll;
  lut.Register(all, allOfAll);

  smarthome::IEventLut::Handlers tempHandlers;
  smarthome::EventDetails temp51(smarthome::Type("temp"), "5", "1");
  lut.Find(temp51, tempHandlers);
  if (tempHandlers.size() != 3) {
    return false;
  }

  smarthome::IEventLut::Handlers tempHandlers2;
  smarthome::EventDetails temp21(smarthome::Type("temp"), "2", "1");
  lut.Find(temp21, tempHandlers2);
  if (tempHandlers2.size() != 2) {
    return false;
  }

  smarthome::IEventLut::Handlers smokeHandlers;
  smarthome::EventDetails smoke24(smarthome::Type("smoke"), "2", "4");
  lut.Find(smoke24, smokeHandlers);
  if (smokeHandlers.size() != 1) {
    return false;
  }

  smarthome::IEventLut::Handlers smokeHandlers2;
  smarthome::EventDetails smoke23(smarthome::Type("smoke"), "2", "3");
  lut.Find(smoke23, smokeHandlers2);
  if (smokeHandlers2.size() != 2) {
    return false;
  }

  smarthome::IEventLut::Handlers lightHandlers;
  smarthome::EventDetails light18(smarthome::Type("light"), "1", "8");
  lut.Find(light18, lightHandlers);
  if (lightHandlers.size() != 1) {
    return false;
  }

  smarthome::IEventLut::Handlers moveHandlers;
  smarthome::EventDetails move96(smarthome::Type("movement"), "9", "6");
  lut.Find(move96, moveHandlers);
  if (moveHandlers.size() != 1) {
    return false;
  }
  
  return true;
}
