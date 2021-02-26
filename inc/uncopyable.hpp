#ifndef UNCOPYABLE_HPP
#define UNCOPYABLE_HPP

namespace smarthome {

class UnCopyable {
public:
  UnCopyable() {}
  // ~UnCopyable() = default

private:
  UnCopyable(const UnCopyable& a_other);
  UnCopyable& operator=(const UnCopyable& a_other);
}; // UnCopyable

}  // smarthome

#endif // UNCOPYABLE_HPP