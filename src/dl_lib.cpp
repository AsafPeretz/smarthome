#include "dl_lib.hpp"
#include <iostream>
#include <errno.h>

namespace smarthome {

/* --------------- FunctionPtr Class --------------- */

FunctionPtr::FunctionPtr()
: m_funcPtr(NULL)
{
}

void FunctionPtr::Init(funcPtr a_func) {
  m_funcPtr = a_func;
}

bool FunctionPtr::IsNull() const {
  return NULL == m_funcPtr;
}

void* FunctionPtr::operator()(const SharedPtr<AgentAdapter>& a_adapter) const { 
  return m_funcPtr(a_adapter);
}

/* --------------- DlLib Class --------------- */

DlLib::DlLib(const std::string& a_filePath, const std::string& a_funcName)
: m_handle(NULL)
, m_funcPtr()
{
  m_handle = dlopen(a_filePath.c_str(), RTLD_LAZY);
  if (NULL == m_handle) {
    std::cout << dlerror() << std::endl;
    libraries::LibraryWasNotFoundException ex;
    throw ex;
  }
  m_funcPtr.Init(reinterpret_cast<funcPtr>(dlsym(m_handle, a_funcName.c_str())));
  if (m_funcPtr.IsNull()) {
    std::cout << dlerror() << std::endl;
    libraries::FunctionWasNotFoundException ex;
    throw ex;
  }
}

DlLib::~DlLib() {
  dlclose(m_handle);
}

FunctionPtr DlLib::GetFunction() {
  return m_funcPtr;
}

} // smarthome
