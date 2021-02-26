#ifndef COMMAND_NOTHING_HPP
#define COMMAND_NOTHING_HPP

#include "command.hpp"

namespace smarthome {

class CommandNothing : public Command {
public:
  CommandNothing() {}
  ~CommandNothing() {}
  void DoCommand() {
    // Doing nothing.
  }
}; // CommandNothing

}  // smarthome

#endif // COMMAND_NOTHING_HPP