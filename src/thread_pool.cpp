#include "thread_pool.hpp"
#include "command_destroy.hpp"
#include "command_cancel.hpp"
#include "command_pause.hpp"
#include <unistd.h>
#include <iostream>

namespace smarthome {

Semaphore g_pause(0);

ThreadPool::ThreadPool(size_t a_numOfThreads)
: m_isActive(true)
, m_commands()
, m_routine(new ThreadPoolRoutine(m_commands, m_isActive))
, m_threads()
, m_numOfThreads(a_numOfThreads) {
  for (size_t i = 0 ; i < a_numOfThreads ; ++i) {
    SharedPtr<Thread> threadToPush(new Thread(m_routine));
    m_threads.push_back(threadToPush);
  }
}

ThreadPool::~ThreadPool() {
  SharedPtr<CommandDestroy> destroy(new CommandDestroy(m_isActive));
  m_commands.Enqueue(destroy);
  for (ThreadsContainer::iterator it = m_threads.begin() ; it != m_threads.end() ; ++it) {
    (*it)->Join();
  }
}

void ThreadPool::Add(const SharedPtr<Command>& a_cmd) {
  m_commands.Enqueue(a_cmd);
}

void ThreadPool::IncThread () {
  SharedPtr<Thread> tr(new Thread(m_routine));
  m_threads.push_back(tr);
  ++m_numOfThreads;
}

void ThreadPool::DecThread () {
  SharedPtr<CommandCancel> cancelthread(new CommandCancel());
  m_commands.Enqueue(cancelthread);
  --m_numOfThreads;
  for (ThreadsContainer::iterator it = m_threads.begin() ; it != m_threads.end() ; ++it) {
    (*it)->TryJoin();
    if (it == m_threads.end()) {
      it = m_threads.begin();
    }
  }
}

void ThreadPool::Pause () {
  CommandPause::SetNumOfThreads(m_numOfThreads);
  for (size_t i = 0 ; i < CommandPause::GetNumOfThreads() ; ++i) {
    SharedPtr<CommandPause> cmd(new CommandPause(g_pause));
    m_commands.Enqueue(cmd);
  }
}

void ThreadPool::Resume () {
  for (size_t i = 0 ; i < CommandPause::GetNumOfThreads() ; ++i) {
    g_pause.Increase();
  }
}

} // smarthome