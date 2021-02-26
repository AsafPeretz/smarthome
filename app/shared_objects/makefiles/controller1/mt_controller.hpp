#ifndef MT_CONTROLLER_HPP
#define MT_CONTROLLER_HPP

#include "mt_event_handle.hpp"
#include "i_sub_manager.hpp"
#include "event_details.hpp"
#include "agent_adapter.hpp"
#include "i_controller.hpp"
#include "shared_ptr.hpp"
#include "agent.hpp"
#include <string>

namespace smarthome {

class MTController : public IController {
public:
  explicit MTController(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~MTController();
  virtual void Start();
  virtual void Subscribe();
  virtual AgentId GetId() const;

private:
  size_t m_id;
  SharedPtr<MTEventHandle> m_handle;
  SharedPtr<ISubManager> m_subManager;
  std::vector<EventDetails> m_subs;

private:
  static size_t m_idPool;

};  // MTController

}  // smarthome

#endif // MT_CONTROLLER_HPP
