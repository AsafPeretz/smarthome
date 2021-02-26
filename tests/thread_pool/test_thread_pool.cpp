#include "command_print_star.hpp"
#include "command_print_dollar.hpp"
#include "thread_pool.hpp"
#include "shared_ptr.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>

int main() {
  const int numOfCommands = 100;
  bool flags[numOfCommands] = { false };
  std::vector<smarthome::SharedPtr<smarthome::Command> > cmd;
  for (int i = 0 ; i < numOfCommands ; ++i) {
    smarthome::SharedPtr<smarthome::Command> cmdTempStar(new smarthome::CommandPrintStar(flags[i]));
    cmd.push_back(cmdTempStar);
    ++i;
    smarthome::SharedPtr<smarthome::Command> cmdTempDollar(new smarthome::CommandPrintDollar(flags[i]));
    cmd.push_back(cmdTempDollar);
  }

  std::cout << "The Test is in process..." << std::endl;
  sleep(1);
  std::cout << "10 more second to finish" << std::endl;

  const int numOfThreads = 4;
  smarthome::ThreadPool pool(numOfThreads);
  for (int i = 0 ; i < numOfCommands ; ++i) {
    pool.Add(cmd[i]);
  }

  sleep(5);
  if (flags[0] && flags[1] && flags[2] && flags[3] && !flags[4] && !flags[5] && !flags[6]) {
    std::cout << std::endl << "Test Passed" << std::endl;
  }
  else {
    std::cout << "Test Failed" << std::endl;
  }

  for (int i = 0 ; i < 10 ; ++i) {
    pool.IncThread();
    // pool.DecThread();
  }
  
  std::cout << "Before Pause and Resume" << std::endl;
  pool.Pause();
  sleep(2);
  pool.Resume();
  std::cout << "After Pause and Resume" << std::endl;
  sleep(1);
  std::cout << "Program finished" << std::endl;
}