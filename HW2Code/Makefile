# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Target executable
TARGET = myrobot

# Source files
SRCS =  MyAlgorithm.cpp MyBatteryMeter.cpp MyDirtSensor.cpp MySimulator.cpp MyWallSensor.cpp House.cpp Vacuum.cpp

HEADERS = abstract_algorithm.h battery_meter.h dirt_sensor.h enums.h House.h MyAlgorithm.h \
          MyBatteryMeter.h MyDirtSensor.h MySimulator.h MyWallSensor.h Vacuum.h wall_sensor.h


# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program with input file
run: $(TARGET)
	./$(TARGET) input.txt

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all run clean
