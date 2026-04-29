CXX ?= g++
TARGET ?= muduo_studying
BUILD_DIR ?= build

SRC_DIRS := $(sort $(dir $(wildcard */*.cpp)))
SRCS := $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

CPPFLAGS += $(addprefix -I,$(SRC_DIRS)) -I.
CXXFLAGS += -std=c++17 -Wall -Wextra -g
LDFLAGS +=
LDLIBS +=

.PHONY: all help run clean rebuild

all: $(TARGET)

help:
	@echo "Usage: make [target]"
	@echo
	@echo "Targets:"
	@echo "  all      Build $(TARGET)"
	@echo "  run      Build and run $(TARGET)"
	@echo "  clean    Remove build outputs"
	@echo "  rebuild  Clean and build again"

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

-include $(DEPS)
