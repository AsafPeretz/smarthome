#ifndef THREAD_POOL_ROUTINE_HPP
#define THREAD_POOL_ROUTINE_HPP

#include "thread_safe_queue.hpp"
#include "atomic_value.hpp"
#include "shared_ptr.hpp"
#include "routine.hpp"
#include "command.hpp"

namespace smarthome {

class ThreadPoolRoutine : public Routine {
public:
  ThreadPoolRoutine(ThreadSafeQueue<SharedPtr<Command> >& a_commands, AtomicValue<bool>& a_funFlag);
  virtual ~ThreadPoolRoutine() {}
  virtual void Do();

private:
  ThreadPoolRoutine(const ThreadPoolRoutine& a_other);
  ThreadPoolRoutine& operator=(const ThreadPoolRoutine& a_other);

private:
  ThreadSafeQueue<SharedPtr<Command> >& m_commands;
  AtomicValue<bool>& m_keepRunning;

}; // ThreadPoolRoutine

}  // smarthome

#endif // THREAD_POOL_ROUTINE_HPP
