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
include simulator/CMakeFiles/myrobot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include simulator/CMakeFiles/myrobot.dir/compiler_depend.make

# Include the progress variables for this target.
include simulator/CMakeFiles/myrobot.dir/progress.make

# Include the compile flags for this target's objects.
include simulator/CMakeFiles/myrobot.dir/flags.make

simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o: simulator/CMakeFiles/myrobot.dir/flags.make
simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o: ../simulator/MySimulator.cpp
simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o: simulator/CMakeFiles/myrobot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o -MF CMakeFiles/myrobot.dir/MySimulator.cpp.o.d -o CMakeFiles/myrobot.dir/MySimulator.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/MySimulator.cpp

simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrobot.dir/MySimulator.cpp.i"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/MySimulator.cpp > CMakeFiles/myrobot.dir/MySimulator.cpp.i

simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrobot.dir/MySimulator.cpp.s"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/MySimulator.cpp -o CMakeFiles/myrobot.dir/MySimulator.cpp.s

simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o: simulator/CMakeFiles/myrobot.dir/flags.make
simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o: ../simulator/AlgorithmRegistrar.cpp
simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o: simulator/CMakeFiles/myrobot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o -MF CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o.d -o CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/AlgorithmRegistrar.cpp

simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.i"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/AlgorithmRegistrar.cpp > CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.i

simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.s"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator/AlgorithmRegistrar.cpp -o CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.s

simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o: simulator/CMakeFiles/myrobot.dir/flags.make
simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o: ../House/House.cpp
simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o: simulator/CMakeFiles/myrobot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o -MF CMakeFiles/myrobot.dir/__/House/House.cpp.o.d -o CMakeFiles/myrobot.dir/__/House/House.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/House/House.cpp

simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrobot.dir/__/House/House.cpp.i"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/House/House.cpp > CMakeFiles/myrobot.dir/__/House/House.cpp.i

simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrobot.dir/__/House/House.cpp.s"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/House/House.cpp -o CMakeFiles/myrobot.dir/__/House/House.cpp.s

simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o: simulator/CMakeFiles/myrobot.dir/flags.make
simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o: ../score/score.cpp
simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o: simulator/CMakeFiles/myrobot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o -MF CMakeFiles/myrobot.dir/__/score/score.cpp.o.d -o CMakeFiles/myrobot.dir/__/score/score.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/score/score.cpp

simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrobot.dir/__/score/score.cpp.i"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/score/score.cpp > CMakeFiles/myrobot.dir/__/score/score.cpp.i

simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrobot.dir/__/score/score.cpp.s"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/score/score.cpp -o CMakeFiles/myrobot.dir/__/score/score.cpp.s

simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o: simulator/CMakeFiles/myrobot.dir/flags.make
simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o: ../vacuum/vacuum.cpp
simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o: simulator/CMakeFiles/myrobot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o -MF CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o.d -o CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o -c /home/jadmahajne/Advanced-topics-in-programming/HW3Code/vacuum/vacuum.cpp

simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.i"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jadmahajne/Advanced-topics-in-programming/HW3Code/vacuum/vacuum.cpp > CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.i

simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.s"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jadmahajne/Advanced-topics-in-programming/HW3Code/vacuum/vacuum.cpp -o CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.s

# Object files for target myrobot
myrobot_OBJECTS = \
"CMakeFiles/myrobot.dir/MySimulator.cpp.o" \
"CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o" \
"CMakeFiles/myrobot.dir/__/House/House.cpp.o" \
"CMakeFiles/myrobot.dir/__/score/score.cpp.o" \
"CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o"

# External object files for target myrobot
myrobot_EXTERNAL_OBJECTS =

simulator/myrobot: simulator/CMakeFiles/myrobot.dir/MySimulator.cpp.o
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/AlgorithmRegistrar.cpp.o
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/__/House/House.cpp.o
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/__/score/score.cpp.o
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/__/vacuum/vacuum.cpp.o
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/build.make
simulator/myrobot: algorithm/libalgorithm1.so
simulator/myrobot: algorithm/libalgorithm2.so
simulator/myrobot: simulator/CMakeFiles/myrobot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable myrobot"
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myrobot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
simulator/CMakeFiles/myrobot.dir/build: simulator/myrobot
.PHONY : simulator/CMakeFiles/myrobot.dir/build

simulator/CMakeFiles/myrobot.dir/clean:
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator && $(CMAKE_COMMAND) -P CMakeFiles/myrobot.dir/cmake_clean.cmake
.PHONY : simulator/CMakeFiles/myrobot.dir/clean

simulator/CMakeFiles/myrobot.dir/depend:
	cd /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jadmahajne/Advanced-topics-in-programming/HW3Code /home/jadmahajne/Advanced-topics-in-programming/HW3Code/simulator /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator /home/jadmahajne/Advanced-topics-in-programming/HW3Code/build/simulator/CMakeFiles/myrobot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : simulator/CMakeFiles/myrobot.dir/depend

