#include "time_stamp.hpp"
#include <string>
#include <iostream>

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_time_stamp(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_time_stamp, testName)
}

static bool Test_time_stamp(std::string& a_testName) {
  a_testName = "Test_time_stamp";
  smarthome::EventTimeStamp ts1("28.07.2020", "10:25:33");
  smarthome::EventTimeStamp ts2;
  if (ts1.GetYear() != "2020" || ts1.GetMonth() != "07" || ts1.GetDay() != "28" || ts1.GetHour() != "10" || ts1.GetMinute() != "25" || ts1.GetSecond() != "33" || ts1.GetDate() != "28.07.2020" || ts1.GetTime() != "10:25:33") {
    return false;
  }
  if (ts2.GetYear() != "2020" || ts2.GetMonth() != "01" || ts2.GetDay() != "01" || ts2.GetHour() != "00" || ts2.GetMinute() != "00" || ts2.GetSecond() != "00" || ts2.GetDate() != "01.01.2020" || ts2.GetTime() != "00:00:00") {
    return false;
  }
  return true;
}
