#include "file_reader.hpp"

namespace smarthome {

FileReader::FileReader(const std::string& a_filePath) {
  m_readFile.open(a_filePath.c_str());
  if (!(m_readFile.is_open())) {  
    FileDoesNotExistException ex;
    throw ex;
  }
}

FileReader::~FileReader() {
  m_readFile.close();
}

std::string FileReader::GetNextLine() {
  std::string number;
  getline(m_readFile, number);
  return number;
}

bool FileReader::IsValid() const {
  return m_readFile.good();
}

} // smarthome