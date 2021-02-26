#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <exception>

namespace smarthome {

namespace CommandExceptions {

struct CancelException : public std::exception {};

} //CommandExceptions

class Command {
public:
  Command() {};
  virtual ~Command() {};
  // Command(const Command a_other) = default
  virtual void DoCommand() = 0;

private:
  Command& operator= (const Command& a_other);
}; // Command

}  // smarthome

#endif // COMMAND_HPP