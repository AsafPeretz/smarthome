  #ifndef SENSOR_HPP
#define SENSOR_HPP

#include "agent.hpp"
#include "i_sub_manager.hpp"
#include "i_event_populator.hpp"

namespace smarthome {

class Sensor : public Agent {
public:
  explicit Sensor(smarthome::SharedPtr<smarthome::IEventPopulator>);
  virtual ~Sensor();
  virtual void Start();
  virtual void Subscribe();
  virtual AgentId GetId() const;

private:
  SharedPtr<IEventPopulator> m_events;

};  // Sensor

}  // smarthome

#endif // SENSOR_HPP