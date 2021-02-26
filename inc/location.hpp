#ifndef EVENT_LOCATION_HPP
#define EVENT_LOCATION_HPP

#include <string>

namespace smarthome {

class EventLocation {
public:
  explicit EventLocation();
  explicit EventLocation(std::string a_floor, std::string a_room);
  EventLocation(const EventLocation& a_other);
  EventLocation& operator=(const EventLocation& a_other);
  bool operator==(const EventLocation& a_locationEvent) const;
  bool operator!=(const EventLocation& a_locationEvent) const;
  const std::string& GetFloor() const;
  const std::string& GetRoom() const;

private:
  std::string m_floor;
  std::string m_room;
}; // EventLocation

}  // smarthome

#endif // EVENT_LOCATION_HPP