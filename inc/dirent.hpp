#ifndef DIRENT_HPP
#define DIRENT_HPP

#include <dirent.h>
#include <string>
#include <exception>

namespace smarthome {

namespace dirent {

struct DirectoryCouldNotOpenException : public std::exception {};

} // dirent

class Dirent {
public:
  Dirent(const std::string& a_dirPath);
  ~Dirent();
  bool GetNextFilePath(std::string& a_dirPathBuffer);

private:
  Dirent(const Dirent& a_other);
  Dirent& operator=(const Dirent& a_other);

private:
  std::string m_dirPath;
  DIR* m_dirent;
  struct dirent *m_dirStruct;
}; // Dirent

} // smarthome

#endif // DIRENT_HPP