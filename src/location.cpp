#include "location.hpp"

namespace smarthome {

EventLocation::EventLocation()
: m_floor()
, m_room()
{
}

EventLocation::EventLocation(std::string a_floor, std::string a_room)
: m_floor(a_floor)
, m_room(a_room)
{
}

EventLocation::EventLocation(const EventLocation& a_other)
: m_floor(a_other.m_floor)
, m_room(a_other.m_room)
{
}

EventLocation& EventLocation::operator=(const EventLocation& a_other) {
  m_floor = a_other.m_floor;
  m_room = a_other.m_room;
  return *this;
}

bool EventLocation::operator==(const EventLocation& a_locationEvent) const {
  return (m_floor == a_locationEvent.m_floor && m_room == a_locationEvent.m_room);
}

bool EventLocation::operator!=(const EventLocation& a_locationEvent) const {
  return !(*this == a_locationEvent);
}

const std::string& EventLocation::GetFloor() const {
  return m_floor;
}

const std::string& EventLocation::GetRoom() const {
  return m_room;
}

}  // smarthome