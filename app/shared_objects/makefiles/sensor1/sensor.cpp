#include "time_stamp.hpp"
#include "shared_ptr.hpp"
#include "rendezvous.hpp"
#include "routine.hpp"
#include "thread.hpp"
#include "sensor.hpp"
#include "event.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace smarthome {

SharedPtr<Event> CreateEvent(bool& a_type);

size_t MTSensor::m_idPool = 1000;

class SensorRoutine : public Routine {
public:
  SensorRoutine(SharedPtr<IEventPopulator>& a_populator)
  : m_events(a_populator)
  , m_type(true)
  {
  }
  virtual ~SensorRoutine() {}
  virtual void Do() {
    srand(time(NULL));
    const size_t numOfEvents = 4;
    for (size_t i = 0 ; i < numOfEvents ; ++i) {
      SharedPtr<Event> event = CreateEvent(m_type);
      m_events->PushEvent(event);
      usleep(100000);
    }
  }

private:
  SharedPtr<IEventPopulator>& m_events;
  bool m_type;
}; // SensorRoutine



MTSensor::MTSensor(const SharedPtr<AgentAdapter> a_adapter)
: ISensor(a_adapter)
, m_id(++m_idPool)
, m_events(this->GetPopulator())
, m_subManager(this->GetSubManager())
{
}

MTSensor::~MTSensor() {
}


void MTSensor::Subscribe() {
}


void MTSensor::Start() {
  m_events = ISensor::GetPopulator();
  SharedPtr<Routine> rout(new SensorRoutine(m_events));
  Thread t1(rout);
  t1.Detach();
}


AgentId MTSensor::GetId() const {
  return m_id;
}


SharedPtr<Event> CreateEvent(bool& a_type) {  
  std::string eventType = ( a_type ? "temp" : "smoke" );
  a_type = (a_type == false);
  
  unsigned int hours = rand() % 12 + 1;
  unsigned int AmPm = rand() % 1 + 1;
  unsigned int realHours = hours * AmPm;
  std::string eventTime = realHours > 19 ? "2" : realHours > 9 ? "1" : "0";
  eventTime += realHours % 10 + '0';
  eventTime += ":";
  for (unsigned int i = 0 ; i < 2 ; ++i) {
    unsigned int minutesTens = rand() % 6 + 1;
    unsigned int minutesunits = rand() % 9 + 1;
    eventTime += minutesTens + '0';
    eventTime += minutesunits + '0';
    eventTime += (i != 1 ? ":" : "");
  }

  std::string eventDate = "05.05.2020";

  std::string tempData = "temp: + 0.";
  unsigned char extraTemp = rand() % 9 + 1;
  tempData += extraTemp + '0';
  std::string eventData = (eventType.compare("temp") == 0 ? tempData : "");

  unsigned char buildingNumber = rand() % 9 + 1;
  std::string building = "Building ";
  building += buildingNumber + '0';

  unsigned char floorNumber = rand() % 9 + 1;
  std::string floor = "Floor ";
  floor += floorNumber + '0';

  unsigned char roomNumber = rand() % 9 + 1;
  std::string room = "Room ";
  room += roomNumber + '0';

  SharedPtr<Event> event (new Event(eventType, EventTimeStamp(eventDate, eventTime), eventData, EventLocation(floor, room)));
  return event;
}

} // smarthome