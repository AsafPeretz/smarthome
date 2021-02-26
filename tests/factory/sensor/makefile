CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3 -fPIC
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(INC_DIR_SENSOR)
CPPFLAGS += -I$(LDLIBS)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread -ldl
INC_DIR = ../../../inc
SRC_DIR = ../../../src
INC_DIR_SENSOR = ./inc
SRC_DIR_SENSOR = ./src
LIB_DIR = ./so
LOGGER_SRC_TEST = ../global_logger
# add shared sources that we depend on
SOURCES_NEEDED = \
	 event.cpp location.cpp mutex.cpp guard_mutex.cpp atomic_counter.cpp cond_var.cpp event_lut.cpp \
	 event_queue.cpp i_distributer.cpp distributer.cpp distribution_mediator.cpp time_stamp.cpp event_details.cpp \
	 i_event_handler.cpp i_event_pool.cpp i_event_populator.cpp i_event_lut.cpp i_sub_manager.cpp i_lut_finder.cpp \
	 thread.cpp rendezvous.cpp readwritemutex.cpp semaphore.cpp guard_semaphore.cpp \
	 dl_lib.cpp agent.cpp agent_adapter.cpp i_sensor.cpp i_event_puller.cpp logger.cpp

SOURCES_FLOW = sensor.cpp sensor_creator.cpp

LOGGER_TEST = global_logger.cpp 

# add private source f  or this target
#SOURCES_MINE = 
TARGET = test_libs

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(foreach src, $(SOURCES_FLOW), $(SRC_DIR_SENSOR)/$(src))
SOURCES += $(foreach src, $(LOGGER_TEST), $(LOGGER_SRC_TEST)/$(src))

#SOURCES += $(SOURCES_MINE)
OBJECTS := $(SOURCES:.cpp=.o)
all : $(TARGET)
$(TARGET):   $(OBJECTS)

	 $ g++ -shared -o $(LIB_DIR)/libsensor.so $(SRC_DIR_SENSOR)/sensor.o $(SRC_DIR_SENSOR)/sensor_creator.o $(LOGGER_SRC_TEST)/global_logger.o \
	 $(SRC_DIR)/i_event_populator.o $(SRC_DIR)/event_queue.o $(SRC_DIR)/i_event_pool.o $(SRC_DIR)/event.o $(SRC_DIR)/event_details.o \
	 $(SRC_DIR)/time_stamp.o $(SRC_DIR)/location.o $(SRC_DIR)/i_sub_manager.o $(SRC_DIR)/mutex.o $(SRC_DIR)/guard_mutex.o $(SRC_DIR)/logger.o \
	 $(SRC_DIR)/rendezvous.o $(SRC_DIR)/i_event_handler.o $(SRC_DIR)/agent_adapter.o $(SRC_DIR)/i_sensor.o $(SRC_DIR)/i_event_puller.o \
	 $(SRC_DIR)/thread.o $(SRC_DIR)/semaphore.o $(SRC_DIR)/agent.o $(SRC_DIR)/cond_var.o $(SRC_DIR)/atomic_counter.o $(SRC_DIR)/i_lut_finder.o \
	 
clean:
	 $(RM) $(TARGET) $(SRC_DIR)/*.o $(SRC_DIR)/*.d $(SRC_DIR_SENSOR)/*.o $(SRC_DIR_SENSOR)/*.d $(LOGGER_SRC_TEST)/*.o $(LOGGER_SRC_TEST)/*.d

cleanl:
	 $(RM) $(LIB_DIR)/libsensor.so

cleanall:
	 $(RM) $(LIB_DIR)/*.so

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)