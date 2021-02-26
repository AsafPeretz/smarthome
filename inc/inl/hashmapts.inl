#ifndef HASHMAPTS_INL
#define HASHMAPTS_INL

/* ---------- Iterator Nested Class function ---------- */

template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional& HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator=(const IteratorBiDirectional& a_other) {
  m_it = a_other.m_it;
  m_index = a_other.m_index;
  return *this;
}

template<class KeyT, class DataT>
bool HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator!=(const IteratorBiDirectional& a_other) {
  return (m_index != a_other.m_index || m_it != a_other.m_it);
}

template<class KeyT, class DataT>
bool HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator==(const IteratorBiDirectional& a_other) {
  return !(*this != a_other);
}

template<class KeyT, class DataT>
std::pair<KeyT, DataT>& HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator*() {
  return *m_it;
}

template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional& HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator++() {
  if (m_it != (*m_mapRef)[m_index].end()) {
    ++m_it;
    if (m_it != (*m_mapRef)[m_index].end()) {
      return *this;
    }
  }
  ++m_index;
  while (m_index < (*m_mapRef).size()) {
    if ((*m_mapRef)[m_index].begin() != (*m_mapRef)[m_index].end()) {
      m_it = (*m_mapRef)[m_index].begin();
      return *this;
    }
    ++m_index;
  }
  --m_index;
  m_it = (*m_mapRef)[m_index].end();
  return *this;
}



template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional& HashMapTS<KeyT, DataT>::IteratorBiDirectional::operator--() {
  if (m_it != (*m_mapRef)[m_index].begin()) {
    --m_it;
    return *this;
  }
  size_t newIndex = m_index;
  while (newIndex > 0) {
    --newIndex;
    if ((*m_mapRef)[newIndex].begin() != (*m_mapRef)[newIndex].end()) {
      m_index = newIndex;
      m_it = (*m_mapRef)[m_index].end();
      --m_it;
      break;
    }
  }
  return *this;
}



/* ---------- HashMapTS Class function ---------- */

template<class KeyT, class DataT>
HashMapTS<KeyT, DataT>::HashMapTS(size_t a_tableSize, HashFunction a_hashFunc, KeysCompareFunction a_keysCompareFunc)
: m_buckets(a_tableSize)
, m_tableSize(a_tableSize)
, m_hashFunc(a_hashFunc)
, m_keysCompareFunc(a_keysCompareFunc)
, m_bucketsRWmutex (new ReadWrite_Mutex [a_tableSize])
{
}

template<class KeyT, class DataT>
HashMapTS<KeyT, DataT>::~HashMapTS() {
  delete [] m_bucketsRWmutex;
}

template<class KeyT, class DataT>
void HashMapTS<KeyT, DataT>::Insert(const KeyT& a_key, const DataT& a_data) {
  size_t index = m_hashFunc(a_key) % m_buckets.size();
  HashMapTSIterator it = FindIterator(a_key, index);

  // check duplicate
  if ((m_buckets)[index].end() != it) {
    throw exceptions::KeyDuplicateException();
  }
  std::pair<KeyT, DataT> newPair(a_key, a_data);

  m_bucketsRWmutex[index].IncWriters();
  (m_buckets)[index].push_back(newPair);
  m_bucketsRWmutex[index].DecWriters();
  return;
}


template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional HashMapTS<KeyT, DataT>::Find(const KeyT& a_key) {
  size_t index = m_hashFunc(a_key) % m_buckets.size();
  m_bucketsRWmutex[index].IncReaders();
  HashMapTSIterator it = FindIterator(a_key, index);
  m_bucketsRWmutex[index].DecReaders();
  return it == m_buckets[index].end() ? End() : IteratorBiDirectional(it, index, this);
}


template<class KeyT, class DataT>
DataT* HashMapTS<KeyT, DataT>::Remove(const KeyT& a_key) {
  size_t index = m_hashFunc(a_key) % m_buckets.size();
  HashMapTSIterator it = FindIterator(a_key ,index);
  if ((m_buckets)[index].end() != it) {
    DataT* returnData = &((*it).second);
    (m_buckets)[index].erase(it);
    return returnData;
  }
  return NULL;
}

template<class KeyT, class DataT>
size_t HashMapTS<KeyT, DataT>::Size() const {
  size_t size = 0;
  for (size_t i = 0 ; i < m_buckets.size() ; ++i) {
    size += m_buckets[0].size();
  }
  return size;
}


template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional HashMapTS<KeyT, DataT>::Begin() {
  size_t i = 0, hashSize = m_buckets.size();
  for ( ; i < hashSize ; ++i) {
    if (0 != (m_buckets)[i].size()) {
      break;
    }
  }
  if (i == hashSize) {
    return End();
  }
  IteratorBiDirectional it((m_buckets)[i].begin(), i, this);
  return it;
}


template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::IteratorBiDirectional HashMapTS<KeyT, DataT>::End() {
  size_t i = m_buckets.size() - 1;
  IteratorBiDirectional it((m_buckets)[i].end(), i, this);
  return it;
}


/* --------------- Local functions --------------- */

template<class KeyT, class DataT>
typename HashMapTS<KeyT, DataT>::HashMapTSIterator HashMapTS<KeyT, DataT>::FindIterator(const KeyT& a_key, size_t a_index) {
  HashMapTSIterator itRun = (m_buckets)[a_index].begin();
  HashMapTSIterator itEnd = (m_buckets)[a_index].end();

  for ( ; itRun != itEnd ; ++itRun) {
    if (m_keysCompareFunc( itRun->first, a_key)) {
      return itRun;
    }
  }
  return itEnd;
}

#endif // HASHMAPTS_INL