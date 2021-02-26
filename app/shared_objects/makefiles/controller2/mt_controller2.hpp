#ifndef MT_CONTROLLER_TWO_HPP
#define MT_CONTROLLER_TWO_HPP

#include "mt_event_handle2.hpp"
#include "i_sub_manager.hpp"
#include "event_details.hpp"
#include "agent_adapter.hpp"
#include "i_controller.hpp"
#include "shared_ptr.hpp"
#include "agent.hpp"
#include <string>

namespace smarthome {

class MTController2 : public IController {
public:
  explicit MTController2(const SharedPtr<AgentAdapter>& a_adapter);
  virtual ~MTController2();
  virtual void Start();
  virtual void Subscribe();
  virtual AgentId GetId() const;

private:
  size_t m_id;
  SharedPtr<MTEventHandle2> m_handle;
  SharedPtr<ISubManager> m_subManager;
  std::vector<EventDetails> m_subs;

private:
  static size_t m_idPool;

};  // MTController2

}  // smarthome

#endif // MT_CONTROLLER_HPP
