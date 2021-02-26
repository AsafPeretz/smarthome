#include "distribution_mediator.hpp"

namespace smarthome {

DistributionMediator::DistributionMediator(const SharedPtr<IEventPuller>& a_events, const SharedPtr<ILutFinder>& a_eventlut)
: m_events(a_events)
, m_eventlut(a_eventlut)
{
}

SharedPtr<Event> DistributionMediator::Mediate(std::vector<SharedPtr<IEventHandler> >& a_handlers) {
  smarthome::SharedPtr<smarthome::Event> event(new smarthome::Event());
  m_events->PopEvent(event);
  m_eventlut->Find(event->GetDetails(), a_handlers);
  return event;
}

} // smarthome
