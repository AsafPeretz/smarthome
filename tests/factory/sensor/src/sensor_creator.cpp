#include "sensor_creator.hpp"
#include "i_agent_creator.hpp"
#include "shared_ptr.hpp"
#include "sensor.hpp"
#include "agent.hpp"
#include <iostream>

namespace smarthome {

DefSensorCreator::DefSensorCreator() {
}

DefSensorCreator::~DefSensorCreator() {
}

SharedPtr<Agent> DefSensorCreator::Create() const {
  SharedPtr<Agent> sensor(new DefSensor);
  return sensor;
}

std::string DefSensorCreator::GetName() const {
  return "DefSensorCreator";
}

} // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator() {
  smarthome::IAgentCreator<smarthome::Agent>* creator = new smarthome::DefSensorCreator;
  return creator;
}

} // extern "C"