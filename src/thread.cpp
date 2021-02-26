#include "thread.hpp"
#include "guard_mutex.hpp"
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include <new>
#include <utility>
#include <iostream>

namespace smarthome {

void* Thread::ThreadFunc(void* a_pair) {
  std::pair<Thread*, SharedPtr<Routine>*> *pair = static_cast<std::pair<Thread*, SharedPtr<Routine>*>*>(a_pair);
  SharedPtr<Routine> rout = *(pair)->second;
  pair->first->m_cord.Notify();
  try {
    rout->Do();
  }catch(const std::exception& ex) {
    std::cout << "Thread routine threw an exception that inherited from std::exception." << std::endl;
  }catch(...) {
    std::cout << "Thread routine threw an exception NOT inherited from std::exception." << std::endl;
  }
  return NULL;
}

Thread::Thread(SharedPtr<Routine> a_threadFunction)
: m_thread()
, m_routine(a_threadFunction)
, m_canJoinOrDetach(true)
, m_lock()
, m_cord()
{
  std::pair<Thread*, SharedPtr<Routine>*> pair = std::make_pair(this, &a_threadFunction);
  int status = pthread_create(&m_thread, 0, ThreadFunc, static_cast<void*>(&pair));
  switch (status) {
    case 0:
      break;
    case EAGAIN:
      throw thread::InsufficientResourcesToCreateException();
    case EPERM:
      throw thread::NoPremissionToCreateException();
    default:
      throw thread::UnKnownException();
  }
  m_cord.Wait();
}

Thread::~Thread() {
  GuardMutex guard(m_lock);
  if (m_canJoinOrDetach) {
    assert(!"Thread DTOR was called without Join, Detach or Cancel ! Shame on you! SHAME !!!!!!!!!!!!!!!!!!!!!");
  }
}

size_t Thread::GetTid() const {
  return m_thread;
}

bool Thread::IsJoinable() const {
  return m_canJoinOrDetach;
}

bool Thread::Detach() { 
  GuardMutex guard(m_lock);
  if (m_canJoinOrDetach) {
    int status = pthread_detach(m_thread);
    switch (status) {
      case 0:
        m_canJoinOrDetach = false;
        return true;
      case EINVAL:
        assert(!"The thread is not joinable");
      case ESRCH:
        assert(!"No thread with this id could be found");
    }
  }
  return false;
}

bool Thread::Cancel() {
  GuardMutex guard(m_lock);
  if (m_canJoinOrDetach) {
    int status = pthread_cancel(m_thread);
    switch (status) {
      case 0:
        m_canJoinOrDetach = false;
        return true;
      case EINVAL:
        assert("Thread::Cancel EINVAL");
    }
  }
  return false;
}


void Thread::Yield() {
  GuardMutex guard(m_lock);
  pthread_yield();
}


bool Thread::Join() {
  GuardMutex guard(m_lock);
  if (m_canJoinOrDetach) {
    int status = pthread_join(m_thread, NULL);
    switch (status) {
      case 0:
        m_canJoinOrDetach = false;
        return true;
      case ESRCH:
        assert(!"No thread with this id could be found");
      case EDEADLK:
        assert(!"DeadLock was detected");
    }
  }
  return false;
}

bool Thread::TryJoin() {
  GuardMutex guard(m_lock);
  if (m_canJoinOrDetach) {
    int status = pthread_tryjoin_np(m_thread, NULL);
    switch (status) {
      case 0:
        m_canJoinOrDetach = false;
        return true;
      // case ESRCH:
      //   assert(!"No thread with this id could be found");
      // case EDEADLK:
      //   assert(!"DeadLock was detected");
    }
  }
  return false;
}

} // smarthome
