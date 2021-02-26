#ifndef COMMAND_PAUSE_HPP
#define COMMAND_PAUSE_HPP

#include "command.hpp"
#include "semaphore.hpp"

namespace smarthome {

class CommandPause : public Command {
public:
  CommandPause(Semaphore& a_pause) : m_pause(a_pause) {}
  ~CommandPause() {}
  void DoCommand() {
    m_pause.DecreaseOrLock();
  }

public:
  static void SetNumOfThreads(size_t a_numOfThreads) { m_numOfPausedThreads = a_numOfThreads; }
  static size_t GetNumOfThreads() { return m_numOfPausedThreads; }

private:
  static size_t m_numOfPausedThreads;

private:
  Semaphore& m_pause;

}; // CommandPause

size_t CommandPause::m_numOfPausedThreads = 0;

}  // smarthome

#endif // COMMAND_PAUSE_HPP