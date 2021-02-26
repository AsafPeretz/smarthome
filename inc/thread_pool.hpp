
#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include "thread_pool_routine.hpp"
#include "thread_safe_queue.hpp"
#include "atomic_value.hpp"
#include "shared_ptr.hpp"
#include "routine.hpp"
#include "command.hpp"
#include "thread.hpp"
#include <list>

namespace smarthome {

class ThreadPool {
public:
  ThreadPool(size_t a_numOfThreads);
  ~ThreadPool();
  void Add(const SharedPtr<Command>& a_cmd);
  void IncThread();
  void DecThread();
  void Pause();
  void Resume();

private:
  ThreadPool(const ThreadPool& a_other);
  ThreadPool& operator=(const ThreadPool& a_other);
  typedef std::list<SharedPtr<Thread> > ThreadsContainer;

private:
  AtomicValue<bool> m_isActive;
  ThreadSafeQueue<SharedPtr<Command> > m_commands;
  SharedPtr<ThreadPoolRoutine> m_routine;
  ThreadsContainer m_threads;
  size_t m_numOfThreads;

}; // ThreadPool

}  // smarthome

#endif // THREAD_POOL_HPP