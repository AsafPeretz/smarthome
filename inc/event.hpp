#ifndef EVENT_HPP
#define EVENT_HPP

#include "event_details.hpp"
#include "time_stamp.hpp"
#include "location.hpp"
#include <string>

namespace smarthome {

typedef std::string EventType;
typedef std::string EventData;

class Event {
public:
  explicit Event();
  explicit Event(EventType a_type, EventTimeStamp a_time, EventData a_data, EventLocation a_location);
  // Event(const Event& a_other) = default
  // Event& operator= (const Event& a_other) = default
  EventType GetType() const;
  EventTimeStamp GetTime() const;
  EventData GetData() const;
  EventLocation GetLocation() const;
  EventDetails GetDetails() const;
  bool operator<(const Event& a_other) const;

private:
  EventType m_type;
  EventTimeStamp m_timeStamp;
  EventData m_data;
  EventLocation m_location;

}; // Event

}  // smarthome

#endif // EVENT_HPP