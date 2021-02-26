#ifndef COND_VAR_HPP
#define COND_VAR_HPP

#include "mutex.hpp"
#include <pthread.h>

namespace smarthome {

class CondVar {
public:
  explicit CondVar();
  ~CondVar();
  // CondVar(const CondVar& a_other) = default
  // CondVar& operator=(const CondVar& a_other) = default
  void Signal();
  void BroadCast();
  
  template<class CondFunc>
  void Wait(Mutex& a_mutex, const CondFunc& a_cond);

private:
  pthread_cond_t m_condVar;

}; // CondVar

#include "./inl/cond_var.inl"

}  // smarthome

#endif // COND_VAR_HPP
