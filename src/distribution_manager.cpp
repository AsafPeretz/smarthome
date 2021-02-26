#include "distribution_manager.hpp"
#include "distribution_mediator.hpp"
#include "distributer.hpp"
#include "command.hpp"
#include <algorithm>
#include "atomic_value.hpp"
#include "thread.hpp"
#include "routine.hpp"
#include <unistd.h>
#include <utility>
#include <vector>
#include <iostream>

namespace smarthome {

DistManager::DistManager(const SharedPtr<IEventPuller>& a_events, const SharedPtr<ILutFinder>& a_eventlut)
: m_dist(new Distributer)
, m_mediator(new DistributionMediator(a_events, a_eventlut))
, m_queueLut()
, m_quePopulator(m_dist)
, m_run(true)
, m_cleanerRun(true)
{
}


void DistManager::Run(const std::vector<SharedPtr<Agent> >& a_agents) {
  createQueuePerAgent(a_agents);
  while (m_run.Get()) {
    SharedPtr<IEventLut::Handlers> handlers(new IEventLut::Handlers);
    SharedPtr<Event> event = m_mediator->Mediate(*handlers);
    for (size_t i = 0 ; i < handlers->size() ; ++i) {
      DistManager::LockQueueLut::iterator itr = m_queueLut.find((*handlers)[i]->GetAgentId());
      SharedPtr<LockQueue>& que = itr->second;
      m_quePopulator.Spread(que, *event, (*handlers)[i]);
    }
  }
}


void DistManager::Pause() {
  m_run = false;
}


void DistManager::createQueuePerAgent(const std::vector<SharedPtr<Agent> >& a_agents) {
  for (size_t i = 0 ; i < a_agents.size() ; ++i) {
    if (m_queueLut.end() == m_queueLut.find(a_agents[i]->GetId())) {
      SharedPtr<LockQueue> que(new LockQueue);
      std::pair<AgentId, SharedPtr<LockQueue> > pair(a_agents[i]->GetId(), que);
      m_queueLut.insert(pair);
    }
  }
}


} // smarthome
