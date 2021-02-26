#ifndef QUEUE_POPULATOR_HPP
#define QUEUE_POPULATOR_HPP

#include "i_event_handler.hpp"
#include "i_distributer.hpp"
#include "thread_pool.hpp"
#include "shared_ptr.hpp"
#include "lock_queue.hpp"
#include "event.hpp"

namespace smarthome {

class QueuePopulator {
public:
  QueuePopulator(SharedPtr<IDistributer>& a_dist, size_t a_numOfThreads = 5);
  // ~QueuePopulator() = default
  void Spread(SharedPtr<LockQueue> a_que, const Event& a_event, const SharedPtr<IEventHandler> a_handler);

private:
  ThreadPool m_threads;
  SharedPtr<IDistributer> m_dist;
  
}; // QueuePopulator

}  // smarthome

#endif // QUEUE_POPULATOR_HPP