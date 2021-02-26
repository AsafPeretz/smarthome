#ifndef DEF_SENSOR_HPP
#define DEF_SENSOR_HPP

#include "i_sub_manager.hpp"
#include "agent.hpp"

namespace smarthome {

class DefSensor : public Agent {
public:
  explicit DefSensor();
  virtual ~DefSensor();
  virtual void Start();
  virtual void Subscribe();
};  // DefSensor

}  // smarthome

#endif // DEF_SENSOR_HPP
