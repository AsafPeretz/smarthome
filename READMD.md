Smarthome

The project is written in C++ 03.

The main class in this system is the CentralHub.
This class communicates with third-party devices (sensors and controllers) by Agent interface (using shared objects and Factory design pattern).

Sensors are devices that collect data from the enviroment and sending it to the central hub.
Controllers are devices that receive data from the sensors (via the central hub), and react accordingly.

The distribution system working is multithreading, and take care for the events order.
The central hub ensures that the events will be sent to the controllers in the order in which they arrive from the sensors.
Each controller can respond to one event of each type simultaneously.

Note:
  some tools were written as new classes (shared_ptr, thread, thread_pool, hash_map, etc.)
