# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Target executable
TARGET = myrobot

# Source files
SRCS = Algorithm.cpp Direction.cpp House.cpp Simulator.cpp Vacuum.cpp

# Header files
HEADERS = Algorithm.h Direction.h House.h Simulator.h Vacuum.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile the source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program with input file and redirect output to output.txt
run: $(TARGET)
	./$(TARGET) input.txt > output.txt

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET) output.txt

# Phony targets
.PHONY: all run clean
