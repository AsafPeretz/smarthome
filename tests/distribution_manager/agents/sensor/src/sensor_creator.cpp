#include "sensor_creator.hpp"


namespace smarthome {

SensorCreator::SensorCreator(const SharedPtr<AgentAdapter>& a_adapter)
: m_adapter(a_adapter)
{
}

SensorCreator::~SensorCreator() {
}

SharedPtr<Agent> SensorCreator::Create() const {
  SharedPtr<MTSensor> sensor(new MTSensor(m_adapter));
  return sensor;
}

std::string SensorCreator::GetName() const {
  return "MTSensor";
}

} // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::AgentAdapter>& a_adapter) {
  smarthome::IAgentCreator<smarthome::Agent>* creator = new smarthome::SensorCreator(a_adapter);
  return creator;
}

} // extern "C"