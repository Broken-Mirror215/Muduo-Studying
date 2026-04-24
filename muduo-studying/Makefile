CXX := g++

TARGET := muduo_studying
BUILD_DIR := build

SRC := \
	Channel/Channel.cpp \
	Epoller/Epoller.cpp \
	Eventloop/Eventloop.cpp \
	main/main.cpp

OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

CXXFLAGS := -std=c++17 -Wall -Wextra -g
CPPFLAGS := -I. -IChannel -IEpoller -IEventloop -Imain
LDFLAGS :=
LDLIBS :=

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEP)
