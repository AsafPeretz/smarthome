CC = g++
CXX = $(CC)

CFLAGS = -ansi -pedantic -Wall -Werror -g3 -fpic
CFLAGS += -pthread

# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -I$(INC_DIR_FLOW)
CPPFLAGS += -I$(LDLIBS)
CPPFLAGS += -MMD -MP
LDLIBS = -lpthread -ldl
INC_DIR = ../../../../../inc
INC_DIR_FLOW = .
SRC_DIR = ../../../../../src
SRC_DIR_FLOW = .
LIB_DIR = ../../so
# add shared sources that we depend on
SOURCES_NEEDED = \
	 event.cpp location.cpp mutex.cpp guard_mutex.cpp atomic_counter.cpp cond_var.cpp event_lut.cpp \
	 event_queue.cpp i_distributer.cpp distributer.cpp distribution_mediator.cpp time_stamp.cpp event_details.cpp \
	 i_event_handler.cpp i_event_pool.cpp i_event_populator.cpp i_event_lut.cpp i_sub_manager.cpp i_lut_finder.cpp \
	 thread.cpp rendezvous.cpp readwritemutex.cpp semaphore.cpp guard_semaphore.cpp \
	 dl_lib.cpp agent.cpp agent_adapter.cpp i_controller.cpp i_event_puller.cpp logger.cpp central_hub.cpp

 SOURCES_FLOW = mt_controller.cpp controller_creator.cpp mt_event_handle.cpp

# add private source f  or this target
#SOURCES_MINE = 
TARGET = test_libs

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
SOURCES += $(foreach src, $(SOURCES_FLOW), $(SRC_DIR_FLOW)/$(src))

#SOURCES += $(SOURCES_MINE)
OBJECTS := $(SOURCES:.cpp=.o)
all : $(TARGET)
$(TARGET):   $(OBJECTS)

	 $ g++ -shared -o $(LIB_DIR)/libcontroller.so $(SRC_DIR_FLOW)/mt_controller.o $(SRC_DIR_FLOW)/controller_creator.o $(SRC_DIR_FLOW)/mt_event_handle.o $(SRC_DIR)/central_hub.o \
	 $(SRC_DIR)/agent.o $(SRC_DIR)/i_event_populator.o $(SRC_DIR)/event_queue.o $(SRC_DIR)/i_event_pool.o $(SRC_DIR)/event.o $(SRC_DIR)/event_details.o \
	 $(SRC_DIR)/time_stamp.o $(SRC_DIR)/location.o $(SRC_DIR)/i_sub_manager.o $(SRC_DIR)/mutex.o $(SRC_DIR)/guard_mutex.o $(SRC_DIR)/cond_var.o $(SRC_DIR)/i_event_puller.o \
	 $(SRC_DIR)/atomic_counter.o $(SRC_DIR)/rendezvous.o  $(SRC_DIR)/i_event_handler.o  $(SRC_DIR)/agent_adapter.o $(SRC_DIR)/i_controller.o $(SRC_DIR)/semaphore.o $(SRC_DIR)/logger.o
	 
clean:
	 $(RM) $(TARGET) $(SRC_DIR)/*.o $(SRC_DIR)/*.d $(SRC_DIR_FLOW)/*.o $(SRC_DIR_FLOW)/*.d

cleanl:
	 $(RM) $(LIB_DIR)/libcontroller.so

cleanall:
	 $(RM) $(LIB_DIR)/*.so

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)