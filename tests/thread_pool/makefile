CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(INC_DIR_POOL)
CPPFLAGS += -I$(INC_DIR_CMD)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread
LDFLAGS = 
INC_DIR = ../../inc
INC_DIR_CMD = ./
SRC_DIR = ../../src
# add shared sources that we depend on
SOURCES_NEEDED = \
	thread.cpp atomic_counter.cpp mutex.cpp guard_mutex.cpp semaphore.cpp guard_semaphore.cpp cond_var.cpp rendezvous.cpp \
	 thread_pool.cpp thread_pool_routine.cpp

TARGET = test_thread_pool

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
	 $(RM) $(TARGET) *.o $(SRC_DIR)/*.o $(SRC_DIR)/*.d *.d *.log
.PHONY: all clean run check grind valgrind helgrind 
#Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)