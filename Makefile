# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

# Target Executable
TARGET = pidOffsetToHex

# Source Files
SRC = pidOffsetToHex.cpp

# Default Target
all: $(TARGET)

# Build Target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up
clean:
	rm -f $(TARGET)

