#include "event_details.hpp"
#include <iostream>

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_details_CTOR(std::string& a_testName);
static bool Test_details_set(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_details_CTOR, testName)
  PRINT_TEST(Test_details_set, testName)
}

static bool Test_details_CTOR(std::string& a_testName) {
  a_testName = "Test_details_CTOR";
  smarthome::EventDetails d1(smarthome::Type("Fire"), "Floor3", "Room1");
  if (d1.GetType().Get() != "Fire" || d1.GetFloor() != "Floor3" || d1.GetRoom() != "Room1") {
    return false;
  }

  smarthome::EventDetails d2(smarthome::Type("Fire"), "Floor3");
  if (d2.GetType().Get() != "Fire" || d2.GetFloor() != "Floor3" || d2.GetRoom() != "Any") {
    return false;
  }

  smarthome::EventDetails d3(smarthome::Type("Fire"));
  if (d3.GetType().Get() != "Fire" || d3.GetFloor() != "Any" || d3.GetRoom() != "Any") {
    return false;
  }

  smarthome::EventDetails d4("Floor3", "Room5");
  if (d4.GetType().Get() != "Any" || d4.GetFloor() != "Floor3" || d4.GetRoom() != "Room5") {
    return false;
  }

  smarthome::EventDetails d5("Floor3");
  if (d5.GetType().Get() != "Any" || d5.GetFloor() != "Floor3" || d5.GetRoom() != "Any") {
    return false;
  }

  smarthome::EventDetails d6;
  if (d6.GetType().Get() != "Any" || d6.GetFloor() != "Any" || d6.GetRoom() != "Any") {
    return false;
  }
  return true;
}


static bool Test_details_set(std::string& a_testName) {
  a_testName = "Test_details_set";
  smarthome::EventDetails details;
  details.SetType("light");
  details.SetFloor("5");
  details.SetRoom("12");
  smarthome::EventDetails d6;
  if (details.GetType().Get() != "light" || details.GetFloor() != "5" || details.GetRoom() != "12") {
    return false;
  }
  return true;
}
