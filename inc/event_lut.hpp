#ifndef EVENT_LUT_HPP
#define EVENT_LUT_HPP

#include "i_event_handler.hpp"
#include "event_details.hpp"
#include "hashmapts.hpp"
#include "i_event_lut.hpp"
#include "shared_ptr.hpp"
#include "event.hpp"
#include <map>

namespace smarthome {

class EventLut : public IEventLut {
public:
  typedef HashMapTS<EventDetails, Handlers> Lut;

public:
  EventLut();
  virtual ~EventLut();
  virtual void Register(SharedPtr<IEventHandler> a_handler, const EventDetails& a_event);
  virtual void UnRegister(const SharedPtr<IEventHandler>& a_handler, const EventDetails& a_event);
  virtual void Find(const EventDetails& a_event, Handlers& a_retval) const;

private:
  void FindInLut(const EventDetails& a_event, Handlers& a_retval) const;

private:
  mutable Lut m_lut;
}; // EventLut

}  // smarthome

#endif // EVENT_LUT_HPP
