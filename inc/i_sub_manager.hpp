#ifndef I_SUB_MANAGER_HPP
#define I_SUB_MANAGER_HPP

#include "i_event_handler.hpp"
#include "event_details.hpp"
#include "uncopyable.hpp"

namespace smarthome {

class ISubManager : private UnCopyable {
public:
  // ISubManager() = delete
  virtual ~ISubManager();
  virtual void Register(SharedPtr<IEventHandler> a_handler, const EventDetails& a_event) = 0;
  virtual void UnRegister(const SharedPtr<IEventHandler>& a_handler, const EventDetails& a_event) = 0;
}; // ISubManager

}  // smarthome

#endif // I_SUB_MANAGER_HPP