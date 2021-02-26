#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP

#include "i_sub_manager.hpp"
#include "agent.hpp"
#include <string>
#include <vector>

namespace smarthome {

class IController : public Agent {
public:
  IController(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~IController() = 0;
  virtual void Subscribe() = 0;
  virtual void Start() = 0;
  virtual AgentId GetId() const = 0;

protected:
  SharedPtr<ISubManager> GetSubManager();
  std::vector<std::string> m_subs;

private:
  SharedPtr<AgentAdapter> m_adapter;
}; // IController

}  // smarthome

#endif // I_CONTROLLER_HPP