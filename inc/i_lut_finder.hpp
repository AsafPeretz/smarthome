#ifndef I_FINDER_HPP
#define I_FINDER_HPP

#include "i_event_handler.hpp"
#include "event_details.hpp"
#include "shared_ptr.hpp"
#include "uncopyable.hpp"
#include <vector>

namespace smarthome {

class ILutFinder : private UnCopyable {
public:
  // ILutFinder() = delete
  virtual ~ILutFinder();
  virtual void Find(const EventDetails& a_event, std::vector<SharedPtr<IEventHandler> >& a_retval) const = 0;
}; // ILutFinder

} // smarthome

#endif // I_FINDER_HPP