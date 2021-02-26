#include "distribution_manager.hpp"
#include "agent_adapter.hpp"
#include "i_sub_manager.hpp"
#include "agent_factory.hpp"
#include "i_lut_finder.hpp"
#include "central_hub.hpp"
#include "event_queue.hpp"
#include "i_event_lut.hpp"
#include "shared_ptr.hpp"
#include "event_lut.hpp"
#include "agent.hpp"
#include <iostream>
#include <vector>

int main() {
  std::cout << std::endl << "*****     " << "For output look at \"logger.text\"" << "     *****" << std::endl << std::endl;
  smarthome::CentralHub cb("devices", "./shared_objects/so", "MakeCreator");
  cb.Start();
}

// BEGIN_TEST(central_hub_test)
//   std::cout << std::endl << "*****     " << "For output look at \"logger.text\"" << "     *****" << std::endl << std::endl;
//   smarthome::CentralHub cb("devices", "./shared_objects/so", "MakeCreator");
//   cb.Start();
//   ASSERT_THAT(true);
// END_TEST


// BEGIN_SUITE(mu test frameqwork demo!)
//     TEST(central_hub_test)
// END_SUITE
