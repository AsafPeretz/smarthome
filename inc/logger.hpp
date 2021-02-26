#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "uncopyable.hpp"
#include "mutex.hpp"
#include <exception>
#include <fstream>
#include <string>

namespace smarthome {

class Logger : private UnCopyable {
public:
  struct FileCouldNotOpenException : public std::exception {};

public:
  Logger();
  ~Logger();
  std::ofstream& operator<<(const std::string& a_text);

private:
  std::ofstream m_file;
  Mutex m_lock;

}; // Logger

}  // smarthome

#endif // LOGGER_HPP