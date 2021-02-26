#include "sensor.hpp"
#include <iostream>

namespace smarthome {

DefSensor::DefSensor()
{
}

DefSensor::~DefSensor() {
}

void DefSensor::Start() {
  std::cout << "Hello ! DefSensor is here!" << std::endl;
}

void DefSensor::Subscribe() {
  return;
}

 
} // smarthome