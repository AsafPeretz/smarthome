#ifndef COND_VAR_INL
#define COND_VAR_INL

template<class CondFunc>
void CondVar::Wait(Mutex& a_mutex, const CondFunc& a_cond) {
  while (a_cond()) {
    pthread_cond_wait(&m_condVar, &a_mutex.m_mutex);
  }
}

#endif // COND_VAR_INL
