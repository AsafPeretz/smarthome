#ifndef I_EVENT_LUT_HPP
#define I_EVENT_LUT_HPP

#include "i_event_handler.hpp"
#include "i_sub_manager.hpp"
#include "event_details.hpp"
#include "i_lut_finder.hpp"
#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include <exception>
#include <vector>

namespace smarthome {

class IEventLut : public ILutFinder, public ISubManager {
public:
  struct DouplicateEventForHandlerException : public std::exception {};
  struct AgentWasNotSubscriberException : public std::exception {};
  typedef std::vector<SharedPtr<IEventHandler> > Handlers;

public:
  // IEventLut() = delete
  virtual ~IEventLut();
  virtual void Register(SharedPtr<IEventHandler> a_handler, const EventDetails& a_event) = 0;
  virtual void UnRegister(const SharedPtr<IEventHandler>& a_handler, const EventDetails& a_event) = 0;
  virtual void Find(const EventDetails& a_event, Handlers& a_retval) const = 0;

}; // IEventLut

}  // smarthome

#endif // I_EVENT_LUT_HPP

