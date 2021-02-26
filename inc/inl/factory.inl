#ifndef FACTORY_INL
#define FACTORY_INL

template<class KeyT, class ObjectBase>
Factory<KeyT, ObjectBase>::Factory()
: m_creators() {
}

template<class KeyT, class ObjectBase>
Factory<KeyT, ObjectBase>::~Factory() {
}

template<class KeyT, class ObjectBase>
SharedPtr<ObjectBase> Factory<KeyT, ObjectBase>::Create(const KeyT& a_key) {
  SharedPtr<IAgentCreator<ObjectBase> > creator = m_creators.find(a_key)->second;
  SharedPtr<ObjectBase> obj = creator->Create();
  return obj;
}

template<class KeyT, class ObjectBase>
void Factory<KeyT, ObjectBase>::Register(const KeyT& a_key, SharedPtr<IAgentCreator<ObjectBase> > a_creator) {
  m_creators.insert(std::pair<KeyT, SharedPtr<IAgentCreator<ObjectBase> > >(a_key, a_creator));
}

#endif // FACTORY_INL