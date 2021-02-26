#include "thread_pool_routine.hpp" 
#include "thread_safe_queue.hpp"
#include "command_nothing.hpp"
#include "atomic_value.hpp"
#include "shared_ptr.hpp"
#include "command.hpp"
//#include "guard_mutex.hpp"

namespace smarthome {

ThreadPoolRoutine::ThreadPoolRoutine(ThreadSafeQueue<SharedPtr<Command> >& a_commands, AtomicValue<bool>& a_funFlag)
: m_commands(a_commands)
, m_keepRunning(a_funFlag) {
}

void ThreadPoolRoutine::Do() {
  Mutex flagLock;
  try {
    while (true) {
      SharedPtr<Command> cmd(new CommandNothing);
      m_commands.Dequeue(cmd);
      cmd->DoCommand();
      //Guard_Mutex flagGuard(flagLock);
      if (m_keepRunning.Compare(0)) {
        m_commands.Enqueue(cmd);
        break;
      }
    }
  }catch(CommandExceptions::CancelException ex) {
  }
}

} // smarthome