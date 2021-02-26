#ifndef HashMapTS_HPP
#define HashMapTS_HPP

#include "readwritemutex.hpp"
#include <vector>
#include <list>
#include <utility> // pair
#include <stddef.h> // size_t
#include <iostream>

namespace smarthome {

namespace exceptions {
struct KeyDuplicateException : std::exception {};
}

template<class KeyT, class DataT>
class HashMapTS {
public:

  // experis::Iterator Nested class
  class IteratorBiDirectional {
  public:
    explicit IteratorBiDirectional(HashMapTS *a_map)
    : m_mapRef(a_map)
    {
    }
    explicit IteratorBiDirectional(typename std::list<std::pair<KeyT, DataT> >::iterator a_itr, size_t a_index, HashMapTS *a_map)
    : m_it(a_itr)
    , m_index(a_index)
    , m_mapRef(a_map)
    {
    }
    // ~IteratorBiDirectiona () = default
    IteratorBiDirectional& operator=(const IteratorBiDirectional& a_other);
    bool operator!=(const IteratorBiDirectional& a_other);
    bool operator==(const IteratorBiDirectional& a_other);
    std::pair<KeyT, DataT>& operator*();
    IteratorBiDirectional& operator++();
    IteratorBiDirectional& operator--();

  private:
    typename std::list<std::pair<KeyT, DataT> >::iterator m_it;
    size_t m_index;
    HashMapTS* m_mapRef;
  }; // experis::Iterator

  typedef int (*HashFunction)(const KeyT& a_key);
  typedef int (*KeysCompareFunction)(const KeyT& a_firstKey, const KeyT& a_secondKey);

public:
  explicit HashMapTS(size_t a_tableSize, HashFunction a_hashFunc, KeysCompareFunction a_keysCompareFunc);
  ~HashMapTS ();
  void Insert(const KeyT& a_key, const DataT& a_data); // throw KeyDuplicateException
  DataT* Remove(const KeyT& a_key);
  IteratorBiDirectional Find(const KeyT& a_key);
  size_t Size() const;
  IteratorBiDirectional Begin();
  IteratorBiDirectional End();

private:
  std::vector<std::list<std::pair<KeyT, DataT> > > m_buckets;
  size_t m_tableSize;
  HashFunction m_hashFunc;
  KeysCompareFunction m_keysCompareFunc;
  ReadWrite_Mutex *m_bucketsRWmutex;

private:
  typedef std::vector<std::list<std::pair<KeyT, DataT> > > Base;
  typedef typename std::list<std::pair<KeyT, DataT> >::iterator HashMapTSIterator;
  HashMapTSIterator FindIterator(const KeyT& a_key, size_t a_index);
  
}; // HashMapTS

#include "./inl/hashmapts.inl"

} // smarthome

#endif // HashMapTS_HPP
