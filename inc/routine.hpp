#ifndef ROUTINE_HPP
#define ROUTINE_HPP

#include "routine.hpp"

namespace smarthome {

class Routine {
public:
  // Routine() == delete
  virtual ~Routine() {}
  virtual void Do() = 0;
}; // Routine
}  // smarthome

#endif // ROUTINE_HPP
