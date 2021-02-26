#ifndef AGENT_HPP
#define AGENT_HPP

#include "agent_adapter.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "semaphore.hpp"
#include <cstddef>

namespace smarthome {

typedef size_t AgentId;

class Agent : private UnCopyable {
public:
  Agent();
  virtual ~Agent();
  virtual void Start() = 0;
  virtual void Subscribe() = 0;
  virtual AgentId GetId() const = 0;

};  // Agent

}  // smarthome

#endif // AGENT_HPP