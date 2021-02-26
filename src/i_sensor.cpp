#include "i_sensor.hpp"

namespace smarthome {

ISensor::ISensor(const SharedPtr<AgentAdapter>& a_adapter)
: m_adapter(a_adapter)
{
}

ISensor::~ISensor() {
}

void ISensor::Subscribe() {
}

SharedPtr<ISubManager> ISensor::GetSubManager() {
  return m_adapter->m_subManager;
}

SharedPtr<IEventPopulator> ISensor::GetPopulator() {
  return m_adapter->m_populator;
}

} // smarthome