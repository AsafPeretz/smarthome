#ifndef I_AGENT_CREATOR_HPP
#define I_AGENT_CREATOR_HPP

#include "shared_ptr.hpp"
#include "agent.hpp"

namespace smarthome {

template<class ValType>
class IAgentCreator {
public:
  // IAgentCreator() = delete
  virtual ~IAgentCreator();
  virtual SharedPtr<ValType> Create() const = 0;
  virtual std::string GetName() const = 0;
};  // IAgentCreator

#include "./inl/i_agent_creator.inl"

}  // smarthome

/*
extern "C" {

smarthome::IAgentCreator<smarthome::Agent>* MakeCreator(const smarthome::SharedPtr<smarthome::IAgentAdapter>& a_adapter);

}
*/

#endif // I_AGENT_CREATOR_HPP