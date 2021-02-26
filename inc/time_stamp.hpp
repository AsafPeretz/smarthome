#ifndef TIME_STAMP_HPP
#define TIME_STAMP_HPP

#include <string>

namespace smarthome {

class EventTimeStamp {
public:
  // date format: 01.01.2020 , time format: 22:01:59
  EventTimeStamp();
  EventTimeStamp(const std::string m_date, const std::string a_time);
  // ~EventTimeStamp() = default
  // EventTimeStamp(const EventTimeStamp& a_other) = default
  // EventTimeStamp& operator=(const EventTimeStamp& a_other) = default
  std::string GetDate() const;
  std::string GetTime() const;
  std::string GetDay() const;
  std::string GetMonth() const;
  std::string GetYear() const;
  std::string GetHour() const;
  std::string GetMinute() const;
  std::string GetSecond() const;
  void SetDate(const std::string& a_date);
  void SetTime(const std::string& a_time);
  
private:
  std::string m_day;
  std::string m_month;
  std::string m_year;
  std::string m_hour;
  std::string m_minute;
  std::string m_second;
}; // EventTimeStamp

}  // smarthome

#endif // TIME_STAMP_HPP