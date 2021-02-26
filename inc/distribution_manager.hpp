#ifndef DISTRIBUTION_MANAGER_HPP
#define DISTRIBUTION_MANAGER_HPP

#include "i_distribution_mediator.hpp"
#include "i_event_puller.hpp"
#include "i_distributer.hpp"
#include "atomic_value.hpp"
#include "i_lut_finder.hpp"
#include "i_event_pool.hpp"
#include "queue_populator.hpp"
#include "atomic_value.hpp"
#include "thread_pool.hpp"
#include "i_event_lut.hpp"
#include "lock_queue.hpp"
#include "semaphore.hpp"
#include "command.hpp"
#include "agent.hpp"
#include "event.hpp"
#include <exception>
#include <vector>
#include <map>

namespace smarthome {

class DistManager {
public:
  struct ControllerHasNoQueueException : public std::exception {};
  typedef std::map<AgentId, SharedPtr<LockQueue> > LockQueueLut;
  
public:
  DistManager(const SharedPtr<IEventPuller>& a_events, const SharedPtr<ILutFinder>& a_eventlut);
  // ~DistManager() = default
  void Run(const std::vector<SharedPtr<Agent> >& a_agents);
  void Pause();

private:
  void createQueuePerAgent(const std::vector<SharedPtr<Agent> >& a_agents);

private:
  SharedPtr<IDistributer> m_dist;
  SharedPtr<IDistributionMediator> m_mediator;
  LockQueueLut m_queueLut;
  QueuePopulator m_quePopulator;
  AtomicValue<bool> m_run; 
  AtomicValue<bool> m_cleanerRun;
}; // DistManager

}  // smarthome

#endif // DISTRIBUTION_MANAGER_HPP
