#ifndef EVENT_DETAILS_HPP
#define EVENT_DETAILS_HPP

#include <string>

namespace smarthome {

class Type {
public:
  Type(const std::string& a_str);
  // ~EventType() default
  // EventType(const EventType& a_other);
  // EventType& operator=(const EventType& a_other);
  bool operator==(const Type& a_other) const;
  bool operator==(const std::string& a_str) const;
  std::string Get() const;
  size_t Size() const;

private:
  std::string m_str;
}; // EventType

class EventDetails {
public:
  EventDetails(const Type& a_eventType, const std::string& a_floor = "Any", const std::string& a_room = "Any");
  EventDetails(const std::string& a_floor = "Any", const std::string& a_room = "Any");
  // ~EventDetails() = default
  // EventDetails(const EventDetails& a_other) = default
  // EventDetails& operator=(const EventDetails& a_other) = default
  bool operator==(const EventDetails& a_other) const;
  bool operator<(const EventDetails& a_other) const;
  Type GetType() const;
  std::string GetFloor() const;
  std::string GetRoom() const;
  void SetType(const std::string a_type);
  void SetFloor(const std::string a_floor);
  void SetRoom(const std::string a_room);

private:
  Type m_eventType;
  std::string m_floor;
  std::string m_room;

}; // EventDetails

}  // smarthome

#endif // EVENT_DETAILS_HPP
