#define QUEUE_DEBUG
#include "thread_safe_queue.hpp"
#include "thread.hpp"
#include "routine.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <utility>

static size_t numOfIterations = 1000000;
static size_t numOfProducing = 1000000;
static size_t numOfThreads = 10;


// Routines for Tests

class MyRoutine : public smarthome::Routine {
public:
  MyRoutine(smarthome::ThreadSafeQueue<size_t*>& a_que) 
  : m_que(a_que)
  {
  }
  virtual ~MyRoutine() {}
  virtual void Do() {
    for (size_t i = 0 ; i < numOfIterations ; ++i) {
      std::pair<size_t*, size_t> temp;
      m_que.Dequeue(temp);
      ++(*temp.first);
      m_que.Enqueue(temp.first);
    }
  }

private:
  smarthome::ThreadSafeQueue<size_t*>& m_que;
}; // MyRoutine


class Producer : public smarthome::Routine {
public:
  Producer(size_t a_init, smarthome::ThreadSafeQueue<size_t>& a_que)
  : m_init(a_init)
  , m_que(a_que)
  {
  }
  virtual ~Producer() {}
  virtual void Do() {
    for (size_t i = m_init ; i < m_init + numOfProducing ; ++i) {
      m_que.Enqueue(i);
    }
  }

private:
  size_t m_init;
  smarthome::ThreadSafeQueue<size_t>& m_que;
}; // Producer


class Concumer : public smarthome::Routine {
public:
  Concumer(std::vector<size_t>& a_little, std::vector<size_t>& a_big, smarthome::ThreadSafeQueue<size_t>& a_que)
  : m_little(a_little)
  , m_big(a_big)
  , m_que(a_que)
  {
  }
  virtual ~Concumer() {}
  virtual void Do() {
    for (size_t i = 0 ; i < numOfProducing ; ++i) {
      std::pair<size_t, size_t> item;
      m_que.Dequeue(item);
      if (item.first < numOfProducing) {
        m_little.push_back(item.second);
      }
      else {
        m_big.push_back(item.second);
      }
    }
  }

private:
  std::vector<size_t>& m_little;
  std::vector<size_t>& m_big;
  smarthome::ThreadSafeQueue<size_t>& m_que;
}; // Consumer


class OneDequeue : public smarthome::Routine {
public:
  OneDequeue(smarthome::ThreadSafeQueue<size_t>& a_que)
  : m_que(a_que)
  {
  }
  virtual ~OneDequeue() {}
  virtual void Do() {
    size_t retval;
    m_que.Dequeue(retval);
  }

private:
  smarthome::ThreadSafeQueue<size_t>& m_que;
}; // OneDequeue


class OneEnqueue : public smarthome::Routine {
public:
  OneEnqueue(smarthome::ThreadSafeQueue<size_t>& a_que)
  : m_que(a_que)
  {
  }
  virtual ~OneEnqueue() {}
  virtual void Do() {
    size_t num = 9;
    m_que.Dequeue(num);
  }

private:
  smarthome::ThreadSafeQueue<size_t>& m_que;
}; // OneEnqueue


class AscendChecker {
public:
  bool operator() (size_t& a_num) {
    size_t* numPtr = &a_num;
    --numPtr;
    return a_num < *numPtr ? true : false;
  }
}; // AscendChecker

bool CheckVecOrder(std::vector<size_t>& a_vec) {
  std::vector<size_t>::iterator sencondItem = a_vec.begin();
  ++sencondItem;
  std::vector<size_t>::iterator itemNotInOrder = std::find_if(sencondItem, a_vec.end(), AscendChecker());
  if (itemNotInOrder != a_vec.end()) {
    return false;
  }
  return true;
}

#define PRINT_TEST(test_func, test_name) \
  { \
    bool result = test_func(test_name); \
    std::cout << test_name << " " << (result ? "Passed" : "Failed") << std::endl; \
  }

static bool Test_Size(std::string& a_testName);
static bool Test_Prod_Conc(std::string& a_testName);
static bool Test_Empty(std::string& a_testName);
static bool Test_Full(std::string& a_testName);
static bool Test_Clear(std::string& a_testName);
static bool Test_DTOR_UNDERFLOW(std::string& a_testName);
static bool Test_DTOR_OVERFLOW(std::string& a_testName);

int main() {
  std::string testName;
  PRINT_TEST(Test_Size, testName)
  PRINT_TEST(Test_Prod_Conc, testName)
  PRINT_TEST(Test_Empty, testName)
  PRINT_TEST(Test_Full, testName)
  PRINT_TEST(Test_Clear, testName)
  PRINT_TEST(Test_DTOR_UNDERFLOW, testName)
  PRINT_TEST(Test_DTOR_OVERFLOW, testName)
}


// Tests

static bool Test_Size(std::string& a_testName) {
  a_testName = "Test_Size";
  std::cout << "The Test in process..." << std::endl;
  sleep(1);
  std::cout << "It takes about 10 seconds." << std::endl;
  size_t *initNumber = new size_t(0);
  smarthome::ThreadSafeQueue<size_t*> que;
  que.Enqueue(initNumber);

  typedef smarthome::SharedPtr<smarthome::Thread> ThreadPtr;
  std::vector<ThreadPtr> vecThreads;
  for (size_t i = 0 ; i < numOfThreads ; ++i) {
    ThreadPtr tr(new smarthome::Thread(smarthome::SharedPtr<MyRoutine>(new MyRoutine(que))));
    vecThreads.push_back(tr);
  }
  for (size_t i = 0 ; i < numOfThreads ; ++i) {
    ThreadPtr tr = vecThreads.back();
    vecThreads.pop_back();
    tr->Join();
  }
  if (*initNumber != numOfThreads * numOfIterations) {
    return false;
  }
  delete initNumber;
  return true;
}


static bool Test_Prod_Conc(std::string& a_testName) {
  a_testName = "Test_Prod_Conc";
  std::vector<size_t> concALittle, concAbig, concBlittle, concBBig;
  smarthome::ThreadSafeQueue<size_t> que;
  smarthome::SharedPtr<Concumer> ConcA(new Concumer(concALittle, concAbig, que));
  smarthome::SharedPtr<Concumer> ConcB(new Concumer(concBlittle, concBBig, que));
  smarthome::SharedPtr<Producer> prodA(new Producer(0, que));
  smarthome::SharedPtr<Producer> prodB(new Producer(numOfProducing, que));
  {
    smarthome::Thread t1(ConcA);
    smarthome::Thread t2(ConcB);
    smarthome::Thread t3(prodA);
    smarthome::Thread t4(prodB);
    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();
  }
  size_t totalSize = concALittle.size() + concAbig.size() + concBlittle.size() + concBBig.size();
  if (totalSize != numOfProducing * 2) {
    return false;
  }
  if (!CheckVecOrder(concALittle) || !CheckVecOrder(concAbig) || !CheckVecOrder(concBlittle) || !CheckVecOrder(concBBig)) {
    return false;
  }
  return true;
}


static bool Test_Empty(std::string& a_testName) {
  a_testName = "Test_Empty";
  smarthome::ThreadSafeQueue<size_t> queue;
  if (!queue.IsEmpty()) {
    return false;
  }
  queue.Enqueue(5);
  queue.Enqueue(11);
  if (queue.IsEmpty()) {
    return false;
  }
  size_t ret1 = 0;
  queue.Dequeue(ret1);
  if (ret1 != 5) {
    return false;
  }
  size_t ret2 = 0;
  queue.Dequeue(ret2);
  if (ret2 != 11) {
    return false;
  }
  if (!queue.IsEmpty()) {
    return false;
  }
  return true;
}


static bool Test_Full(std::string& a_testName) {
  a_testName = "Test_Full";
  smarthome::ThreadSafeQueue<size_t> queue(2);
  if (queue.IsFull()) {
    return false;
  }
  queue.Enqueue(8);
  if (queue.IsFull()) {
    return false;
  }
  queue.Enqueue(11);
  if (!queue.IsFull()) {
    return false;
  }
  size_t retVal = 0;
  queue.Dequeue(retVal);
  if (queue.IsFull()) {
    return false;
  }
  queue.Dequeue(retVal);
  if (queue.IsFull()) {
    return false;
  }
  return true;
}


static bool Test_Clear(std::string& a_testName) {
  a_testName = "Test_Clear";
  const size_t queueSize = 5;
  smarthome::ThreadSafeQueue<size_t> queue(queueSize);
  for (size_t i = 0 ; i < queueSize ; ++i) {
    queue.Enqueue(i);
  }
  if (!queue.IsFull() || queue.Size() != queueSize) {
    return false;
  }
  queue.Clear();
  if (!queue.IsEmpty() || queue.Size() != 0) {
    return false;
  }
  queue.Clear();
  queue.Enqueue(8);
  if (queue.IsEmpty()) {
    return false;
  }
  queue.Clear();
  if (!queue.IsEmpty()) {
    return false;
  }
  return true;
}


static bool Test_DTOR_UNDERFLOW(std::string& a_testName) {
  a_testName = "Test_DTOR_UNDERFLOW";
  smarthome::ThreadSafeQueue<size_t> *que = new smarthome::ThreadSafeQueue<size_t>;
  smarthome::SharedPtr<OneDequeue> OneDeq(new OneDequeue(*que));
  smarthome::Thread t1(OneDeq);
  const size_t halfSecond = 500000;
  usleep(halfSecond);
  delete que;
  t1.Join();
  return true;
}


static bool Test_DTOR_OVERFLOW(std::string& a_testName) {
  a_testName = "Test_DTOR_OVERFLOW";
  smarthome::ThreadSafeQueue<size_t> *que = new smarthome::ThreadSafeQueue<size_t>(2);
  smarthome::SharedPtr<OneEnqueue> OneEnq(new OneEnqueue(*que));
  smarthome::Thread t1(OneEnq);
  smarthome::Thread t2(OneEnq);
  smarthome::Thread t3(OneEnq);
  const size_t halfSecond = 500000;
  usleep(halfSecond);
  delete que;
  t1.Join();
  t2.Join();
  t3.Join();
  return true;
}