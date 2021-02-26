#ifndef MT_SENSOR_HPP
#define MT_SENSOR_HPP

#include "i_event_populator.hpp"
#include "i_sub_manager.hpp"
#include "rendezvous.hpp"
#include "i_sensor.hpp"
#include "rendezvous.hpp"
#include "agent.hpp"

namespace smarthome {

class MTSensor : public ISensor {
public:
  explicit MTSensor(const SharedPtr<AgentAdapter> a_adapter);
  virtual ~MTSensor();
  virtual void Start();
  virtual void Subscribe();
  virtual AgentId GetId() const;

private:
  size_t m_id;
  SharedPtr<IEventPopulator> m_events;
  SharedPtr<ISubManager> m_subManager;

private:
  static size_t m_idPool;

};  // MTSensor

}  // smarthome

#endif // MT_SENSOR_HPP