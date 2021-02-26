#ifndef I_EVENT_HANDLE_HPP
#define I_EVENT_HANDLE_HPP

#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include <vector>

namespace smarthome {

class IEventHandler : private UnCopyable {
public:
  typedef size_t AgentId;
public:
  // IEventHandler() = default
  virtual ~IEventHandler();
  virtual void HandleEvent(const SharedPtr<Event>& a_event) = 0;
  virtual AgentId GetAgentId() const = 0;

}; // IEventHandler

} // smarthome

#endif // I_EVENT_HANDLE_HPP
