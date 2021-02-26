#include "event_lut.hpp"
#include "event_details.hpp"
#include "event.hpp"
#include <algorithm>
#include <iostream>

namespace smarthome {

class DuplicateCheck {
public:
  DuplicateCheck(const SharedPtr<IEventHandler>& a_newHandler)
  : m_handler(a_newHandler)
  {
  }
  void operator()(const SharedPtr<IEventHandler>& a_handler) const {
    if (m_handler == a_handler) {
      throw IEventLut::DouplicateEventForHandlerException();
    }
  }

private:
  const SharedPtr<IEventHandler>& m_handler;
}; // DuplicateCheck

int HashFunc(const EventDetails& a_key) {
  Type type = a_key.GetType();
  std::string floor = a_key.GetFloor();
  std::string room = a_key.GetRoom();
  int retval = type.Size() + floor.size() + floor.size();
  retval *= 103;
  retval *= type.Size();
  retval *= floor[0];
  retval <<= 2;
  return retval;
}

int CompareFunc(const EventDetails& a_firstKey, const EventDetails& a_secondKey) {
  return a_firstKey == a_secondKey;
}

// EventLut

EventLut::EventLut()
: m_lut(1000, HashFunc, CompareFunc)
{
}

EventLut::~EventLut() {
}

void EventLut::Register(SharedPtr<IEventHandler> a_handler, const EventDetails& a_event) {
  Lut::IteratorBiDirectional itr = m_lut.Find(a_event);
  if (itr == m_lut.End()) {
    Handlers newHandler;
    newHandler.push_back(a_handler);
    m_lut.Insert(a_event, newHandler);
    return;
  }
  Handlers& agents = (*itr).second;
  std::for_each(agents.begin(), agents.end(), DuplicateCheck(a_handler));
  agents.push_back(a_handler);
}

void EventLut::Find(const EventDetails& a_event, Handlers& a_retval) const {  
  Handlers agents;
  
  // (Type, Floor, Room)
  EventDetails detailsForFind = a_event;
  FindInLut(detailsForFind, agents);

  // (Type, Floor, Any)
  detailsForFind.SetRoom("Any");
  FindInLut(detailsForFind, agents);

  // (Type, Any, Any)
  detailsForFind.SetFloor("Any");
  FindInLut(detailsForFind, agents);

  // (Any, Any, Any)
  detailsForFind.SetType("Any");
  FindInLut(detailsForFind, agents);

  // (Any, Floor, Any)
  detailsForFind.SetFloor(a_event.GetFloor());
  FindInLut(detailsForFind, agents);

  // (Any, Floor, Room)
  detailsForFind.SetRoom(a_event.GetRoom());
  FindInLut(detailsForFind, agents);

  std::unique(agents.begin(), agents.end());

  a_retval = agents;
}

void EventLut::UnRegister(const SharedPtr<IEventHandler>& a_handler, const EventDetails& a_event) {
  Lut::IteratorBiDirectional itr = m_lut.Find(a_event);
  if (itr == m_lut.End()) {
    throw AgentWasNotSubscriberException();
  }
  Handlers& relevantHandler = (*itr).second;
  Handlers::iterator handlerItr = std::find(relevantHandler.begin(), relevantHandler.end(), a_handler);
  if (handlerItr == relevantHandler.end()) {
    throw AgentWasNotSubscriberException();
  }
  relevantHandler.erase(handlerItr);
}



/* --------------- Local Functions --------------- */

void EventLut::FindInLut(const EventDetails& a_event, Handlers& a_retval) const {
  Lut::IteratorBiDirectional itr = m_lut.Find(a_event);
  if (itr != m_lut.End()) {
    Handlers& relevantHandler = (*itr).second;
    a_retval.insert(a_retval.end(), relevantHandler.begin(), relevantHandler.end());
  }
}

} // smarthome