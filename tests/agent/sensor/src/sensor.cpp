#include "sensor.hpp"
#include "event.hpp"
#include "time_stamp.hpp"
#include "shared_ptr.hpp"
#include <string>
#include <stdlib.h>

namespace smarthome {

Sensor::Sensor(smarthome::SharedPtr<smarthome::IEventPopulator> a_populator)
: m_events(a_populator)
{
}

Sensor::~Sensor() {
}

void Sensor::Start() {
  SharedPtr<Event> eventPtr(new Event("TypeA", EventTimeStamp("05.05.2020" ,"22:05:01"), "temp: +0.2", EventLocation("Landing", "Lobby")));
  m_events->PushEvent(eventPtr);
}

void Sensor::Subscribe() {
}

AgentId Sensor::GetId() const {
  return 1;
}


} // smarthome