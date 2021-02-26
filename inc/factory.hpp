#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "i_agent_creator.hpp"
#include "shared_ptr.hpp"
#include "uncopyable.hpp"
#include <utility>
#include <map>

namespace smarthome {

template<class KeyT, class ObjectBase>
class Factory : private UnCopyable {
public:
  Factory();  
  ~Factory();
  SharedPtr<ObjectBase> Create(const KeyT& a_key);
  void Register(const KeyT& a_key, SharedPtr<IAgentCreator<ObjectBase> > a_creator);

private:
  std::map<KeyT, SharedPtr<IAgentCreator<ObjectBase> > > m_creators;

}; // Factory

#include "./inl/factory.inl"

}  // smarthome

#endif // FACTORY_HPP
