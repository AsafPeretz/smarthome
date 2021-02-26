#ifndef SENSOR_CREATOR_HPP
#define SENSOR_CREATOR_HPP

#include "i_agent_creator.hpp"
#include "shared_ptr.hpp"
#include "sensor.hpp"

namespace smarthome {

class DefSensorCreator : public IAgentCreator<Agent> {
public:
  DefSensorCreator();
  virtual ~DefSensorCreator();
  virtual SharedPtr<Agent> Create() const;
  virtual std::string GetName() const;
};  // DefSensorCreator

}  // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator();

}

#endif // SENSOR_CREATOR_HPP
