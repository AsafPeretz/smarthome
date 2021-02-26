#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include <exception>
#include "mutex.hpp"
#include "routine.hpp"
#include "shared_ptr.hpp"
#include "rendezvous.hpp"
#include "uncopyable.hpp"

namespace smarthome {

namespace thread {
struct InsufficientResourcesToCreateException : public std::exception {
};
struct NoPremissionToCreateException : public std::exception {
};
struct UnKnownException : public std::exception {
};
} // exceptions

class Thread : private UnCopyable {
public:
  explicit Thread(SharedPtr<Routine> a_threadFunction);
  virtual~Thread();
  size_t GetTid() const;
  bool IsJoinable() const;
  bool Detach();
  bool Cancel();
  bool Join();
  bool TryJoin();
  void Yield();

private:
static void* ThreadFunc(void* a_routine);

private:
  pthread_t m_thread;
  SharedPtr<Routine> m_routine;
  bool m_canJoinOrDetach;
  Mutex m_lock;
  Rendezvous m_cord;
}; // Thread

}  // smarthome

#endif // THREAD_HPP
