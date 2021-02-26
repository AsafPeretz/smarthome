CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(INC_DIR_AGENTS)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread
LDFLAGS = 
INC_DIR = ../../inc
INC_DIR_AGENTS = ./agents/inc
SRC_DIR = ../../src
SRC_DIR_AGENTS = ./agents/src
# add shared sources that we depend on
SOURCES_NEEDED = \
	 event.cpp location.cpp atomic_counter.cpp event_lut.cpp event_lut.cpp i_event_lut.cpp i_lut_finder.cpp \
	 i_event_handler.cpp i_event_lut.cpp time_stamp.cpp event_details.cpp location.cpp i_sub_manager.cpp \
	 readwritemutex.cpp semaphore.cpp guard_semaphore.cpp

SOURCES_MINE = event_handle.cpp

TARGET = test_event_lut

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(foreach src, $(SOURCES_MINE), $(SRC_DIR_AGENTS)/$(src))

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
	 $(RM) $(TARGET) *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d *.d *.log $(SRC_DIR_AGENTS)/*.o $(SRC_DIR_AGENTS)/*.d
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)