#ifndef I_DISTRIBUTION_MEDIATOR_HPP
#define I_DISTRIBUTION_MEDIATOR_HPP

#include "i_event_handler.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"
#include <vector>

namespace smarthome {

class IDistributionMediator : private UnCopyable {
public:
  virtual ~IDistributionMediator();
  virtual SharedPtr<Event> Mediate(std::vector<SharedPtr<IEventHandler> >& a_handlers) = 0;

}; // IDistributionMediator

}  // smarthome

#endif // I_DISTRIBUTION_MEDIATOR_HPP