#ifndef COMMAND_PRINT_STAR_HPP
#define COMMAND_PRINT_STAR_HPP

#include "command.hpp"
#include <iostream>
#include <unistd.h>

namespace smarthome {

class CommandPrintStar : public Command {
public:
  CommandPrintStar(bool& a_flag) : m_flag(a_flag) {};
  virtual ~CommandPrintStar() {};
  // Command(const Command a_other) = default
  virtual void DoCommand() {
    sleep(3);
    m_flag = true;
    std::cout << "**********" << std::endl;
  }

private:
  Command& operator= (const Command& a_other);

private:
  bool& m_flag;
}; // CommandPrintStar

}  // smarthome

#endif // COMMAND_PRINT_STAR_HPP