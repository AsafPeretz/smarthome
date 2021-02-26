#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include "uncopyable.hpp"
#include <exception>
#include <fstream>
#include <string>

namespace smarthome {

class FileReader : private UnCopyable {
public:
  struct FileDoesNotExistException : std::exception {};

public:
  FileReader(const std::string& a_filePath);
  ~FileReader();
  std::string GetNextLine();
  bool IsValid() const;

private:
  std::ifstream m_readFile;
}; // FileReader

}  // smarthome

#endif // FILE_READER_HPP