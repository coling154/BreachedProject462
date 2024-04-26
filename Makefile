# Compiler
CC = g++

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c++17 -O2

# Directories
SRC_DIR = src
BUILD_DIR = build

# Target executable
TARGET = breachedApp

# Find all C++ source files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files to be built, one for each source file
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Link object files into a binary
$(BUILD_DIR)/breachedApp: $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -pthread

# make build directory, if it does not exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

#clean rule to clean build directory
clean:
	rm -rf $(BUILD_DIR)