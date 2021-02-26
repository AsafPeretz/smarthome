#include "queue_populator.hpp"
#include "command.hpp"
#include <utility>
#include <iostream>

namespace smarthome {

class DistCommand : public Command {
public:
  DistCommand(SharedPtr<LockQueue>& a_lockQue, SharedPtr<IDistributer>& a_dist, ThreadPool& a_threads)
  : m_lockQue(a_lockQue)
  , m_dist(a_dist)
  , m_threads(a_threads)
  {
  }
  virtual ~DistCommand() {}
  virtual void DoCommand() {
    const size_t iterations = 2;
    for (size_t i = iterations ; i && !m_lockQue->Empty() ; --i) {
      std::pair<Event, SharedPtr<IEventHandler> > pair(Event(),SharedPtr<IEventHandler>(NULL));
      m_lockQue->Dequeue(pair);
      SharedPtr<Event> eventPtr(new Event(pair.first));
      m_dist->Distribute(eventPtr, pair.second);
    }
    if (!m_lockQue->Empty()) {
      SharedPtr<Command> cmd(new DistCommand(m_lockQue, m_dist, m_threads));
      m_threads.Add(cmd);
    }
    m_lockQue->SetNonActive();
  }

private:
  SharedPtr<LockQueue> m_lockQue;
  SharedPtr<IDistributer> m_dist;
  ThreadPool& m_threads;
}; // DistCommand


QueuePopulator::QueuePopulator(SharedPtr<IDistributer>& a_dist, size_t a_numOfThreads)
: m_threads(a_numOfThreads)
, m_dist(a_dist)
{
}

void QueuePopulator::Spread(SharedPtr<LockQueue> a_que, const Event& a_event, const SharedPtr<IEventHandler> a_handler) {
  if (a_que->IsActive()) {
    a_que->Enqueue(std::pair<Event, SharedPtr<IEventHandler> >(a_event, a_handler));
  }
  else {
    a_que->SetActive();
    a_que->Enqueue(std::pair<Event, SharedPtr<IEventHandler> >(a_event, a_handler));
    SharedPtr<Command> cmd(new DistCommand(a_que, m_dist, m_threads));
    m_threads.Add(cmd);
  }
}

}  // smarthome