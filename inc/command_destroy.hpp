#ifndef COMMAND_DESTROY_HPP
#define COMMAND_DESTROY_HPP

#include "atomic_value.hpp"
#include "command.hpp"
//#include "guard_mutex.hpp"

namespace smarthome {

class CommandDestroy : public Command {
public:
  CommandDestroy(AtomicValue<bool>& a_flagRun) : m_flagRun(a_flagRun) {}
  ~CommandDestroy() {}
  void DoCommand() {
    //Guard_Mutex flagRunGuard(m_flag);
    m_flagRun = false;
  }
private:
  AtomicValue<bool>& m_flagRun;
  Mutex m_flag;
}; // CommandDestroy

}  // smarthome

#endif // COMMAND_DESTROY_HPP