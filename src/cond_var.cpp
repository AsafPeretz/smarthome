#include "cond_var.hpp"

namespace smarthome {

CondVar::CondVar()
: m_condVar()
{
  pthread_cond_init(&m_condVar, NULL);
}

CondVar::~CondVar() {
}

void CondVar::Signal() {
  pthread_cond_signal(&m_condVar);
}

void CondVar::BroadCast() {
  pthread_cond_broadcast(&m_condVar);
}

} // smarthome
