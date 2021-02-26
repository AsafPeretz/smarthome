CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(MU_TEST_DIR)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread
LDFLAGS = 
INC_DIR = ../../inc
MU_TEST_DIR = ../
SRC_DIR = ../../src
# add shared sources that we depend on
SOURCES_NEEDED = time_stamp.cpp
# add private source f  or this target
#SOURCES_MINE =
TARGET = test_time_stamp

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
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
	 $(RM) $(TARGET) *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d *.d *.log
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)