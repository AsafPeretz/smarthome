#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <exception>
#include <semaphore.h>

namespace smarthome {

namespace semaphore{
struct ValueOutOfBoundsException : public std::exception {};
struct SystemDoesntSupportProccesSharedException : public std::exception {};
struct WasInterruptedBySignalHandlerException : public std::exception {};
struct UnknownException : public std::exception {};
}

class Semaphore {
public:
  Semaphore();
  Semaphore(unsigned int a_initValue);
  Semaphore(unsigned int a_initValue, bool a_sharedBetweenProcesses);
  ~Semaphore();
  void Increase();
  void DecreaseOrLock();

private:
  Semaphore(const Semaphore& a_other);
  const Semaphore& operator= (const Semaphore& a_other);

private:
  sem_t m_semaphore;
}; // Semaphore

}  // smarthome


#endif // SEMAPHORE_HPP