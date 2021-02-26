CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(INC_DIR_TEST)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread
LDFLAGS = 
INC_DIR = ../../inc
INC_DIR_TEST = sensor/inc
SRC_DIR = ../../src
SRC_DIR_TEST = sensor/src
# add shared sources that we depend on
SOURCES_NEEDED = \
		agent.cpp event_queue.cpp event.cpp location.cpp i_event_puller.cpp \
		mutex.cpp guard_mutex.cpp atomic_counter.cpp cond_var.cpp \
		i_event_pool.cpp i_event_populator.cpp time_stamp.cpp event_details.cpp logger.cpp

SOURCES_TEST = sensor.cpp 
# add private source f  or this target
#SOURCES_MINE = producer.cpp consumer.cpp
TARGET = test_sensor

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(foreach src, $(SOURCES_TEST), $(SRC_DIR_TEST)/$(src))
#SOURCES += $(SOURCES_MINE)
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
	 $(RM) $(TARGET) $(SRC_DIR)/*.o $(SRC_DIR)/*.d $(SRC_DIR_TEST)/*.o $(SRC_DIR_TEST)/*.d *.o *.d
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)
