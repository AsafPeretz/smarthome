CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -MMD -MP
CPPFLAGS += -I$(LDLIBS)
LDLIBS = -lpthread -ldl
INC_DIR = ../../inc
SRC_DIR = ../../src
LOGGER_SRC_TEST = ./global_logger
# add shared sources that we depend on
SOURCES_NEEDED = \
		agent.cpp event_queue.cpp i_event_pool.cpp mutex.cpp guard_mutex.cpp event.cpp location.cpp time_stamp.cpp \
		cond_var.cpp atomic_counter.cpp i_event_populator.cpp logger.cpp \
		dirent.cpp dl_lib.cpp i_sensor.cpp agent_adapter.cpp i_controller.cpp semaphore.cpp i_lut_finder.cpp i_event_puller.cpp \
		event_lut.cpp i_event_lut.cpp readwritemutex.cpp i_event_handler.cpp event_details.cpp i_sub_manager.cpp
		
# add private source f  or this targe
LOGGER_TEST = global_logger.cpp 

TARGET = test_factory

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(foreach src, $(LOGGER_TEST), $(LOGGER_SRC_TEST)/$(src))

OBJECTS := $(SOURCES:.cpp=.o)
all : $(TARGET)
$(TARGET):   $(OBJECTS)
run:  $(TARGET)
	 ./$(TARGET)
check: clean run
grind: valgrind helgrind
valgrind:  $(TARGET)
	 valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes ./$(TARGET) 
helgrind:  $(TARGET)
	 valgrind --tool=helgrind --log-file=helgrind.log ./$(TARGET) 
clean:
	 $(RM) $(TARGET) *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d *.d *.log $(LOGGER_SRC_TEST)/*.o $(LOGGER_SRC_TEST)/*.d
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)