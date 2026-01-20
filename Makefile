# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS = 

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = cache_sim

# Default target
all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

test: $(TARGET)
	@echo "=== Testing Direct-Mapped (1-way) on conflict trace ==="
	./$(TARGET) $(TEST_DIR)/conflict.txt
	@echo ""
	@echo "=== Testing on sequential trace ==="
	./$(TARGET) $(TEST_DIR)/seq_trace.txt

.PHONY: all clean test

#make debug
print-%:
	@echo $*