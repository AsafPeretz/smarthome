#ifndef COMMAND_PRINT_DOLLAR_HPP
#define COMMAND_PRINT_DOLLAR_HPP

#include "command.hpp"
#include <iostream>
#include <unistd.h>

namespace smarthome {

class CommandPrintDollar : public Command {
public:
  CommandPrintDollar(bool& a_flag) : m_flag(a_flag) {};
  virtual ~CommandPrintDollar() {};
  // Command(const Command a_other) = default
  virtual void DoCommand() {
    sleep(3);
    m_flag = true;
    std::cout << "$$$$$$$$$$" << std::endl;
  }

private:
  Command& operator= (const Command& a_other);

private:
  bool& m_flag;
}; // CommandPrintDollar

}  // smarthome

#endif // COMMAND_PRINT_DOLLAR_HPP