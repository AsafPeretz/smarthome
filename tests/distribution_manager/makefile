CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(LDLIBS)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread -ldl
LDFLAGS = 
INC_DIR = ../../inc
SRC_DIR = ../../src

SOURCES_NEEDED = \
	 event.cpp location.cpp mutex.cpp guard_mutex.cpp atomic_counter.cpp cond_var.cpp \
	 event_lut.cpp event_queue.cpp \
	 i_distributer.cpp distributer.cpp distribution_mediator.cpp time_stamp.cpp event_details.cpp\
	 i_event_handler.cpp i_event_pool.cpp i_event_populator.cpp i_event_lut.cpp i_sub_manager.cpp agent.cpp \
	 thread.cpp rendezvous.cpp i_lut_finder.cpp readwritemutex.cpp semaphore.cpp guard_semaphore.cpp logger.cpp \
	 i_sensor.cpp i_controller.cpp agent_adapter.cpp dirent.cpp dl_lib.cpp agent_factory.cpp distribution_manager.cpp \
	 i_lut_finder.cpp i_event_pool.cpp i_agent_factory.cpp thread_pool.cpp thread_pool_routine.cpp i_distribution_mediator.cpp \
	 i_event_puller.cpp queue_populator.cpp lock_queue.cpp

TARGET = test_dist_manager

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))


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
	 $(RM) $(TARGET) *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d *.d *.log $(SRC_DIR_FLOW)/*.o $(SRC_DIR_FLOW)/*.d
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)