#include "event_details.hpp"
#include <iostream>

namespace smarthome {

// EventType

Type::Type(const std::string& a_str)
: m_str(a_str)
{
}

bool Type::operator==(const Type& a_other) const {
  return m_str == a_other.m_str;
}

bool Type::operator==(const std::string& a_str) const {
  return m_str == a_str;
}

std::string Type::Get() const {
  return m_str;
}

size_t Type::Size() const {
  return m_str.size();
}

// EventDetails

EventDetails::EventDetails(const Type& a_eventType, const std::string& a_floor, const std::string& a_room)
: m_eventType(a_eventType)
, m_floor(a_floor)
, m_room(a_room)
{
}

EventDetails::EventDetails(const std::string& a_floor, const std::string& a_room)
: m_eventType(Type("Any"))
, m_floor(a_floor)
, m_room(a_room)
{
}

bool EventDetails::operator==(const EventDetails& a_other) const {
  bool type = (GetType() == a_other.GetType());
  bool floor = (GetFloor() == a_other.GetFloor());
  bool room = (GetRoom() == a_other.GetRoom());
  return type && floor && room;
}

bool EventDetails::operator<(const EventDetails& a_other) const {
  return !(*this == a_other);
}

Type EventDetails::GetType() const {
  return m_eventType;
}

std::string EventDetails::GetFloor() const {
  return m_floor;
}

std::string EventDetails::GetRoom() const {
  return m_room;
}

void EventDetails::SetType(const std::string a_eventType) {
  m_eventType = a_eventType;
}

void EventDetails::SetFloor(const std::string a_floor) {
  m_floor = a_floor;
}

void EventDetails::SetRoom(const std::string a_room) {
  m_room = a_room;
}

} // smarthome
