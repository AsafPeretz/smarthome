#include "distributer.hpp"
#include <algorithm>
#include <iostream>

namespace smarthome {

Distributer::~Distributer() {
}

void Distributer::Distribute(SharedPtr<Event>& a_event, SharedPtr<IEventHandler> a_handler) {
  a_handler->HandleEvent(a_event);
}

} // smarthome
