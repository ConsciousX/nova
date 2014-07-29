include test.mk

CXXFLAGS += -std=c++11 -Wall
#LDFLAGS +=
CXX = g++

SOURCE_PATH = src
INCLUDE_PATH = include
BINARY_PATH = bin
OBJECT_PATH = obj
LIB_PATH = lib
DEP_PATH = obj

BUILD_MODE ?= release
ifeq ($(BUILD_MODE),debug)
	CXXFLAGS += -ggdb -O0
else
	ifeq ($(BUILD_MODE),release)
		CXXFLAGS += -O3
	else
		$(error "BUILD_MODE error!(debug/release)")
	endif
endif

VPATH = $(SOURCE_PATH)

OBJECTS := $(patsubst %.cpp, $(OBJECT_PATH)/%.o, $(SOURCES))
DEPS := $(patsubst %.cpp, $(DEP_PATH)/%.d, $(SOURCES))
TARGET := $(BINARY_PATH)/$(TARGET)

all: .MKDIR $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LDFALGS) -o $@

$(OBJECT_PATH)/%.o : $(SOURCE_PATH)/%.cpp
	$(CXX) -c $(CXXFLAGS) -I$(INCLUDE_PATH) $< -o $@

$(DEP_PATH)/%.d: %.cpp
	@echo -n "$(DEP_PATH)/" > $@
	$(CXX) -I$(INCLUDE_PATH) -MM $< > $@

.MKDIR:
	@if [ ! -d $(OBJECT_PATH) ]; then mkdir -p $(OBJECT_PATH); fi
	@if [ ! -d $(BINARY_PATH) ]; then mkdir -p $(BINARY_PATH); fi
	@if [ ! -d $(LIB_PATH) ]; then mkdir -p $(LIB_PATH); fi

clean:
	rm -rf $(BINARY_PATH)/ $(OBJECT_PATH)/ $(LIB_PATH)/

-include $(DEPS)

.PHONY: all
