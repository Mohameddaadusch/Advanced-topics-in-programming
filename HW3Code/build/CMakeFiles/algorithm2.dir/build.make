# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jadmahajne/Advanced-topics-in-programming/HW3Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build

# Include any dependencies generated for this target.
include CMakeFiles/algorithm2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/algorithm2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/algorithm2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/algorithm2.dir/flags.make

CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o: CMakeFiles/algorithm2.dir/flags.make
CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o: ../algorithm/Algorithm2/Algo_123456789.cpp
CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o: CMakeFiles/algorithm2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o -MF CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o.d -o CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/algorithm/Algorithm2/Algo_123456789.cpp

CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/algorithm/Algorithm2/Algo_123456789.cpp > CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.i

CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/algorithm/Algorithm2/Algo_123456789.cpp -o CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.s

# Object files for target algorithm2
algorithm2_OBJECTS = \
"CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o"

# External object files for target algorithm2
algorithm2_EXTERNAL_OBJECTS =

libalgorithm2.so: CMakeFiles/algorithm2.dir/algorithm/Algorithm2/Algo_123456789.cpp.o
libalgorithm2.so: CMakeFiles/algorithm2.dir/build.make
libalgorithm2.so: CMakeFiles/algorithm2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libalgorithm2.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/algorithm2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/algorithm2.dir/build: libalgorithm2.so
.PHONY : CMakeFiles/algorithm2.dir/build

CMakeFiles/algorithm2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/algorithm2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/algorithm2.dir/clean

CMakeFiles/algorithm2.dir/depend:
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jadmahajne/Advanced-topics-in-programming/HW3Code /home/jadmahajne/Advanced-topics-in-programming/HW3Code /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles/algorithm2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/algorithm2.dir/depend

