#include "event.hpp"

namespace smarthome {

Event::Event()
: m_type()
, m_timeStamp()
, m_data()
, m_location()
{
}

Event::Event(EventType a_type, EventTimeStamp a_time, EventData a_data, EventLocation a_location)
: m_type(a_type)
, m_timeStamp(a_time)
, m_data(a_data)
, m_location(a_location)
{
}

EventType Event::GetType() const {
  return m_type;
}

EventTimeStamp Event::GetTime() const {
  return m_timeStamp;
}

EventData Event::GetData() const {
  return m_data;
}

EventLocation Event::GetLocation() const {
  return m_location;
}

EventDetails Event::GetDetails() const {
  return EventDetails(m_type, m_location.GetFloor(), m_location.GetRoom());
}

} // smarthome