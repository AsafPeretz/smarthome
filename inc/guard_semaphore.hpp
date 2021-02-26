#ifndef GUARD_SEMAPHORE_HPP
#define GUARD_SEMAPHORE_HPP

#include "semaphore.hpp"

namespace smarthome {

class Guard_Semaphore {
public:
  Guard_Semaphore(Semaphore& a_downNpost);
  void Forget();
  ~Guard_Semaphore();
private:
  Semaphore& m_down;
  bool m_post;
}; // Guard_Semaphore

}  // smarthome

#endif // GUARD_SEMAPHORE_HPP