#ifndef DL_LIB_HPP
#define DL_LIB_HPP

#include <dlfcn.h>
#include <string>
#include <exception>
#include "shared_ptr.hpp"
#include "agent_adapter.hpp"

namespace smarthome {

namespace libraries {

struct LibraryWasNotFoundException : public std::exception {};
struct FunctionWasNotFoundException : public std::exception {};

} // exceptions

class FunctionPtr {
  typedef void*(*funcPtr)(const SharedPtr<AgentAdapter>& a_adapter);

public:
  void Init(funcPtr a_func);
  bool IsNull() const;
  void* operator()(const SharedPtr<AgentAdapter>& a_adapter) const;

  private:
    FunctionPtr();
    friend class DlLib;

private:
  funcPtr m_funcPtr;
}; // FunctionPtr


class DlLib {
public:
  DlLib(const std::string& a_filePath, const std::string& a_funcName);
  ~DlLib();
  FunctionPtr GetFunction();

private:
  typedef void*(*funcPtr)(const SharedPtr<AgentAdapter>& a_adapter);

private:
  void* m_handle;
  FunctionPtr m_funcPtr;

}; // DlLib

}  // smarthome


#endif // DL_LIB_HPP