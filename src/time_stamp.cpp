#include "time_stamp.hpp"
#include <string>

namespace smarthome {

EventTimeStamp::EventTimeStamp()
: m_day("01")
, m_month("01")
, m_year("2020")
, m_hour("00")
, m_minute("00")
, m_second("00")
{
}

EventTimeStamp::EventTimeStamp(const std::string a_date, const std::string a_time)
: m_day(a_date.substr(0, 2))
, m_month(a_date.substr(m_day.size() + 1, 2))
, m_year(a_date.substr(m_day.size() + m_month.size() + 2, 4))
, m_hour(a_time.substr(0, 2))
, m_minute(a_time.substr(m_hour.size() + 1, 2))
, m_second(a_time.substr(m_hour.size() + m_minute.size() + 2, 2))
{
}

std::string EventTimeStamp::GetDate() const {
  std::string date = m_day + "." + m_month + "." + m_year;
  return date;
}

std::string EventTimeStamp::GetTime() const {
  std::string time = m_hour + ":" + m_minute + ":" + m_second;
  return time;
}

std::string EventTimeStamp::GetDay() const {
  return m_day;
}

std::string EventTimeStamp::GetMonth() const {
  return m_month;
}

std::string EventTimeStamp::GetYear() const {
  return m_year;
}

std::string EventTimeStamp::GetHour() const {
  return m_hour;
}

std::string EventTimeStamp::GetMinute() const {
  return m_minute;
}

std::string EventTimeStamp::GetSecond() const {
  return m_second;
}

void EventTimeStamp::SetDate(const std::string& a_date) {
  m_day = a_date.substr(0, 2);
  m_month = a_date.substr(m_day.size() + 1, 2);
  m_year = a_date.substr(m_month.size() + m_day.size() + 2, 4);
}

void EventTimeStamp::SetTime(const std::string& a_time) {
  m_hour = a_time.substr(0, 2);
  m_minute = a_time.substr(m_hour.size() + 1, 2);
  m_second = a_time.substr(m_hour.size() + m_minute.size() + 2, 2);
}

} // smarthome