#ifndef I_DISTRIBUTER_HPP
#define I_DISTRIBUTER_HPP

#include "i_event_lut.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"

namespace smarthome {

class IDistributer : private UnCopyable {
public:
  // IDistributer() = default
  virtual ~IDistributer();
  virtual void Distribute(SharedPtr<Event>& a_event, SharedPtr<IEventHandler> a_handler) = 0;
}; // IDistributer

}  // smarthome

#endif // I_DISTRIBUTER_HPP
