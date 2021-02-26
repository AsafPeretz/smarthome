#ifndef COMMAND_CANCEL_HPP
#define COMMAND_CANCEL_HPP

#include "command.hpp"

namespace smarthome {

class CommandCancel : public Command {
public:
  CommandCancel() {}
  ~CommandCancel() {}
  void DoCommand() {
    CommandExceptions::CancelException ex;
    throw ex;
  }
}; // CommandCancel

}  // smarthome

#endif // COMMAND_CANCEL_HPP