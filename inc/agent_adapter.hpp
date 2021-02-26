#ifndef AGENT_ADAPTER_HPP
#define AGENT_ADAPTER_HPP

#include "i_event_populator.hpp"
#include "i_sub_manager.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"

namespace smarthome {

class AgentAdapter {
public:
  AgentAdapter(const SharedPtr<ISubManager>& a_subManager, const SharedPtr<IEventPopulator>& a_populator);
  virtual ~AgentAdapter();

private:
  SharedPtr<ISubManager> m_subManager;
  SharedPtr<IEventPopulator> m_populator;

friend class ISensor;
friend class IController;
}; // AgentAdapter

}  // smarthome

#endif // AGENT_ADAPTER_HPP