#ifndef SENSOR_CREATOR_HPP
#define SENSOR_CREATOR_HPP

#include "i_agent_creator.hpp"
#include "agent_adapter.hpp"
#include "shared_ptr.hpp"
#include "sensor.hpp"
#include "agent.hpp"

namespace smarthome {

class SensorCreator : public IAgentCreator<Agent> {
public:
  SensorCreator(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~SensorCreator();
  virtual SharedPtr<Agent> Create() const;
  virtual std::string GetName() const;
  
private:
  SharedPtr<AgentAdapter> m_adapter;
};  // SensorCreator

}  // smarthome

extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::AgentAdapter>& a_adapter);

}

#endif // SENSOR_CREATOR_HPP
