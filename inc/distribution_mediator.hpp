#ifndef DISTRIBUTION_MEDIATOR_HPP
#define DISTRIBUTION_MEDIATOR_HPP

#include "i_distribution_mediator.hpp"
#include "i_event_puller.hpp"
#include "i_lut_finder.hpp"

namespace smarthome {

class DistributionMediator : public IDistributionMediator {
public:
  DistributionMediator(const SharedPtr<IEventPuller>& a_event, const SharedPtr<ILutFinder>& a_eventlut);
  // ~DistributionMediator() = default
  virtual SharedPtr<Event> Mediate(std::vector<SharedPtr<IEventHandler> >& a_handlers);

private:
  SharedPtr<IEventPuller> m_events;
  SharedPtr<ILutFinder> m_eventlut;

}; // DistributionMediator

}  // smarthome

#endif // DISTRIBUTION_MEDIATOR_HPP