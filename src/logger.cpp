#include "logger.hpp"
#include <iostream>

namespace smarthome {

Logger::Logger()
: m_file()
, m_lock()
{
  const std::string logFile = "./logger.text";
  m_file.open(logFile.c_str(), std::ofstream::app);
  if (!(m_file.is_open())) {  
    FileCouldNotOpenException ex;
    throw ex;
  }
}

Logger::~Logger() {
  m_file.close();
}

std::ofstream& Logger::operator<<(const std::string& a_text) {
  m_lock.Lock();
  m_file << a_text;
  m_lock.UnLock();
  return m_file;
}

} // smarthome
