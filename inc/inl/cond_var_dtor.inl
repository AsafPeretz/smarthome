#ifndef COND_VAR_DTOR_INL
#define COND_VAR_DTOR_INL

class CondVarDtor {
public:
  CondVarDtor(AtomicValue<size_t>& a_val, size_t a_expected)
  : m_val(a_val),
  m_expected(a_expected)
  {
  }
  //~CondVarDtor();
  bool operator()() const {
    return (!m_val.Compare(m_expected));
  }
  
private:
  AtomicValue<size_t>& m_val;
  size_t m_expected;
}; // CondVarDtor

#endif // COND_VAR_DTOR_INL
