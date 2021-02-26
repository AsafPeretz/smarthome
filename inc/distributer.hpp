#ifndef DISTRIBUTER_HPP
#define DISTRIBUTER_HPP

#include "i_distributer.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include <vector>

namespace smarthome {

class Distributer : public IDistributer {
public:
  // Distributer() = default
  virtual ~Distributer();
  virtual void Distribute(SharedPtr<Event>& a_event, SharedPtr<IEventHandler> a_handler);
}; // Distributer

}  // smarthome

#endif // DISTRIBUTER_HPP
