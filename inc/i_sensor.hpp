#ifndef I_SENSOR_HPP
#define I_SENSOR_HPP

#include "i_event_populator.hpp"
#include "agent_adapter.hpp"
#include "i_sub_manager.hpp"
#include "agent.hpp"

namespace smarthome {

class ISensor : public Agent {
public:
  ISensor(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~ISensor() = 0;
  virtual void Subscribe() = 0;
  virtual void Start() = 0;
  virtual AgentId GetId() const = 0;

protected:
  SharedPtr<ISubManager> GetSubManager();
  SharedPtr<IEventPopulator> GetPopulator();

private:
  SharedPtr<AgentAdapter> m_adapter;
}; // ISensor

}  // smarthome

#endif // I_SENSOR_HPP
