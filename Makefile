# Compiler and flags
CXX = g++
INCLUDE_DIR = include
LIBRARY_DIR = lib
CXXFLAGS = -std=c++20 -g -Wall -I$(INCLUDE_DIR) -I$(LIBRARY_DIR)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Project name
TARGET = SheepFight

# Source and object files
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)


# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Build target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)