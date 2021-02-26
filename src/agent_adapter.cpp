#include "agent_adapter.hpp"

namespace smarthome {

AgentAdapter::AgentAdapter(const SharedPtr<ISubManager>& a_subManager, const SharedPtr<IEventPopulator>& a_populator)
: m_subManager(a_subManager)
, m_populator(a_populator)
{
}

AgentAdapter::~AgentAdapter() {
}

} // smarthome