include test.mk

CXXFLAGS=-O3 -g -std=c++11 -Wall
CXX=g++

SOURCE_PATH=src
INCLUDE_PATH=include
BINARY_PATH=bin
OBJECT_PATH=obj
LIB_PATH=lib
DEP_PATH=obj

VPATH=$(SOURCE_PATH)

OBJECTS:=$(patsubst %.cpp, $(OBJECT_PATH)/%.o, $(SOURCES))
DEPS:=$(patsubst %.cpp, $(DEP_PATH)/%.d, $(SOURCES))
TARGET:=$(BINARY_PATH)/$(TARGET)

$(shell mkdir $(BINARY_PATH))
$(shell mkdir $(LIB_PATH))
$(shell mkdir $(OBJECT_PATH))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

$(OBJECTS): $(OBJECT_PATH)/%.o : $(SOURCE_PATH)/%.cpp
	$(CXX) -c $(CXXFLAGS) -I$(INCLUDE_PATH) $< -o $@

%.d : %.cpp
	@set -e; rm -f $@; \
	$(CXX) -I$(INCLUDE_PATH) $(CXXFLAGS) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SOURCES:.cpp=.d)

.PHONY: all

clean:
	rm -rf $(BINARY_PATH) $(OBJECT_PATH) $(LIB_PATH)
