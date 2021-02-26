#include "dirent.hpp"

namespace smarthome {

bool DirStructValidation(struct dirent* a_dirStruct);

Dirent::Dirent(const std::string& a_dirPath)
: m_dirPath(a_dirPath)
, m_dirent(opendir(a_dirPath.c_str()))
, m_dirStruct()
{
  if (NULL == m_dirent) {
    throw dirent::DirectoryCouldNotOpenException();
  }
}

Dirent::~Dirent() {
  closedir(m_dirent);
}

bool Dirent::GetNextFilePath(std::string& a_dirPathBuffer) {
  m_dirStruct = readdir(m_dirent);
  if (false == DirStructValidation(m_dirStruct)) {
    return false;
  }

  a_dirPathBuffer = m_dirPath;
  a_dirPathBuffer += "/";
  a_dirPathBuffer += m_dirStruct->d_name;
  return true;
}



/* --------------- Local Function --------------- */

bool DirStructValidation(struct dirent* a_dirStruct) {
  if (NULL == a_dirStruct) {
    return false;
  }
  std::string fileName = a_dirStruct->d_name;
  if (0 == fileName.compare(".") || 0 == fileName.compare("..") ) {
    return false;
  }
  return true;
}

} // smarthome