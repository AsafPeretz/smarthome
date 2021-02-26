#include "thread.hpp"
#include "routine.hpp"
#include "shared_ptr.hpp"
#include "rendezvous.hpp"
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

smarthome::Rendezvous g_multiDetachCord;
smarthome::Rendezvous g_singleDetachCord;


// Routines for Tests

class OneRoutine : public smarthome::Routine {
public:
  OneRoutine(bool& a_bool) 
  : m_bool(a_bool) 
  {
  }
  virtual ~OneRoutine() {}
  virtual void Do() {
    m_bool = false;
  }

private:
  bool& m_bool;
}; // OneRoutine


class DelayRoutine : public smarthome::Routine {
public:
  DelayRoutine(bool& a_bool) 
  : m_bool(a_bool) 
  {
  }
  virtual ~DelayRoutine() {}
  virtual void Do() {
    const size_t billion = 1000000000;
    for (volatile size_t i = 0 ; i < billion ; ++i) {
    }
    m_bool = false;
  }

private:
  bool& m_bool;
}; // DelayRoutine


class CordMultiDetachRoutine : public smarthome::Routine {
public:
  CordMultiDetachRoutine(bool& a_bool) 
  : m_bool(a_bool) 
  {
  }
  virtual ~CordMultiDetachRoutine() { g_multiDetachCord.Notify(); }
  virtual void Do() {
    m_bool = false;
  }

private:
  bool& m_bool;
}; // CordMultiDetachRoutine


class CordSingleDetachRoutine : public smarthome::Routine {
public:
  CordSingleDetachRoutine(bool& a_bool) 
  : m_bool(a_bool) 
  {
  }
  virtual ~CordSingleDetachRoutine() { g_singleDetachCord.Notify(); }
  virtual void Do() {
    m_bool = false;
  }

private:
  bool& m_bool;
}; // CordSingleDetachRoutine



#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_ThreadCancel(std::string& a_testName);
static bool Test_MultiDetach(std::string& a_testName);
static bool Test_OneThreadDetach(std::string& a_testName);
static bool Test_MuiltiJoin(std::string& a_testName);
static bool Test_OneThreadJoin(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_ThreadCancel, testName)
  PRINT_TEST(Test_MultiDetach, testName)
  PRINT_TEST(Test_OneThreadDetach, testName)
  PRINT_TEST(Test_MuiltiJoin, testName)
  PRINT_TEST(Test_OneThreadJoin, testName)
}


// Tests

static bool JoinNtimes(size_t a_numOfThreads, size_t a_numOfJoins);


static bool Test_OneThreadJoin(std::string& a_testName) {
  a_testName = "OneThreadJoin";
  return (JoinNtimes(1, 1));
}

static bool Test_MuiltiJoin(std::string& a_testName) {
  a_testName = "MuiltiJoin";
  return JoinNtimes(4, 4);
}

static bool Test_OneThreadDetach(std::string& a_testName) {
  a_testName = "OneThreadDetach";
  bool flagFalseByRoutine = true;
  {
    smarthome::SharedPtr<CordMultiDetachRoutine> rout(new CordMultiDetachRoutine(flagFalseByRoutine));
    smarthome::Thread t1(rout);
    t1.Detach();
  }
  g_multiDetachCord.Wait();
  return flagFalseByRoutine ? false : true;
}

static bool Test_MultiDetach(std::string& a_testName) {
  a_testName = "MultiDetach";
  bool flagFalseByRoutine = true;
  {
    smarthome::SharedPtr<CordSingleDetachRoutine> rout(new CordSingleDetachRoutine(flagFalseByRoutine));
    smarthome::Thread t1(rout);
    for (size_t i = 0 ; i < 5 ; ++i) {
      t1.Detach();
    }
  }
  g_singleDetachCord.Wait();
  return flagFalseByRoutine ? false : true;
}

static bool Test_ThreadCancel(std::string& a_testName) {
  a_testName = "ThreadCancel";
  bool flag1 = true;
  smarthome::SharedPtr<DelayRoutine> one(new DelayRoutine(flag1));
  smarthome::Thread t1(one);
  t1.Cancel();
  return flag1 ? true : false;
}



// Function for Tests

static bool JoinNtimes(size_t a_numOfThreads, size_t a_numOfJoins) {
  std::vector<smarthome::SharedPtr<bool> > bools;
  std::vector<smarthome::SharedPtr<OneRoutine> > routines;
  std::vector<smarthome::SharedPtr<smarthome::Thread> > threads;
  for (size_t i = 0 ; i < a_numOfThreads ; ++i) {
    bools.push_back(smarthome::SharedPtr<bool>(new bool(true)));
    routines.push_back(smarthome::SharedPtr<OneRoutine>(new OneRoutine(*bools[i])));
    threads.push_back(smarthome::SharedPtr<smarthome::Thread>(new smarthome::Thread(routines.back())));
  }
  for (size_t i = 0 ; i < a_numOfThreads * a_numOfJoins ; ++i) {
    threads[i % a_numOfThreads]->Join();
  }
  bool retval = true;
  for (size_t i = 0 ; i < a_numOfThreads ; ++i) {
    if (*bools[i]) {
      retval = false;
    }
  }
  return retval;
}
