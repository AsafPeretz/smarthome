#ifndef THREAD_SAFE_QUEUE_CONDFUNC_INL
#define THREAD_SAFE_QUEUE_CONDFUNC_INL

class CondVarFunc {
public:
  CondVarFunc(AtomicValue<size_t>& a_val, size_t a_expected, AtomicValue<bool>& a_stop)
  : m_val(a_val),
  m_expected(a_expected),
  m_stop(a_stop)
  {
  }
  //~CondVarFunc();
  bool operator()() const {
    return (m_val.Compare(m_expected) && m_stop.Compare(false));
  }

private:
  AtomicValue<size_t>& m_val;
  size_t m_expected;
  AtomicValue<bool>& m_stop;
}; // CondVarFunc


#endif // THREAD_SAFE_QUEUE_CONDFUNC_INL