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
CMAKE_SOURCE_DIR = /home/ant/Downloads/gol-1/gol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ant/Downloads/gol-1/gol

# Include any dependencies generated for this target.
include CMakeFiles/conway.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/conway.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/conway.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conway.dir/flags.make

CMakeFiles/conway.dir/main.c.o: CMakeFiles/conway.dir/flags.make
CMakeFiles/conway.dir/main.c.o: main.c
CMakeFiles/conway.dir/main.c.o: CMakeFiles/conway.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ant/Downloads/gol-1/gol/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/conway.dir/main.c.o"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/conway.dir/main.c.o -MF CMakeFiles/conway.dir/main.c.o.d -o CMakeFiles/conway.dir/main.c.o -c /home/ant/Downloads/gol-1/gol/main.c

CMakeFiles/conway.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conway.dir/main.c.i"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ant/Downloads/gol-1/gol/main.c > CMakeFiles/conway.dir/main.c.i

CMakeFiles/conway.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conway.dir/main.c.s"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ant/Downloads/gol-1/gol/main.c -o CMakeFiles/conway.dir/main.c.s

CMakeFiles/conway.dir/logic.c.o: CMakeFiles/conway.dir/flags.make
CMakeFiles/conway.dir/logic.c.o: logic.c
CMakeFiles/conway.dir/logic.c.o: CMakeFiles/conway.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ant/Downloads/gol-1/gol/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/conway.dir/logic.c.o"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/conway.dir/logic.c.o -MF CMakeFiles/conway.dir/logic.c.o.d -o CMakeFiles/conway.dir/logic.c.o -c /home/ant/Downloads/gol-1/gol/logic.c

CMakeFiles/conway.dir/logic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conway.dir/logic.c.i"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ant/Downloads/gol-1/gol/logic.c > CMakeFiles/conway.dir/logic.c.i

CMakeFiles/conway.dir/logic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conway.dir/logic.c.s"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ant/Downloads/gol-1/gol/logic.c -o CMakeFiles/conway.dir/logic.c.s

CMakeFiles/conway.dir/render.c.o: CMakeFiles/conway.dir/flags.make
CMakeFiles/conway.dir/render.c.o: render.c
CMakeFiles/conway.dir/render.c.o: CMakeFiles/conway.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ant/Downloads/gol-1/gol/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/conway.dir/render.c.o"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/conway.dir/render.c.o -MF CMakeFiles/conway.dir/render.c.o.d -o CMakeFiles/conway.dir/render.c.o -c /home/ant/Downloads/gol-1/gol/render.c

CMakeFiles/conway.dir/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conway.dir/render.c.i"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ant/Downloads/gol-1/gol/render.c > CMakeFiles/conway.dir/render.c.i

CMakeFiles/conway.dir/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conway.dir/render.c.s"
	mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ant/Downloads/gol-1/gol/render.c -o CMakeFiles/conway.dir/render.c.s

# Object files for target conway
conway_OBJECTS = \
"CMakeFiles/conway.dir/main.c.o" \
"CMakeFiles/conway.dir/logic.c.o" \
"CMakeFiles/conway.dir/render.c.o"

# External object files for target conway
conway_EXTERNAL_OBJECTS =

conway: CMakeFiles/conway.dir/main.c.o
conway: CMakeFiles/conway.dir/logic.c.o
conway: CMakeFiles/conway.dir/render.c.o
conway: CMakeFiles/conway.dir/build.make
conway: /usr/lib/x86_64-linux-gnu/libSDL2main.a
conway: /usr/lib/x86_64-linux-gnu/libSDL2.so
conway: CMakeFiles/conway.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ant/Downloads/gol-1/gol/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable conway"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conway.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conway.dir/build: conway
.PHONY : CMakeFiles/conway.dir/build

CMakeFiles/conway.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conway.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conway.dir/clean

CMakeFiles/conway.dir/depend:
	cd /home/ant/Downloads/gol-1/gol && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ant/Downloads/gol-1/gol /home/ant/Downloads/gol-1/gol /home/ant/Downloads/gol-1/gol /home/ant/Downloads/gol-1/gol /home/ant/Downloads/gol-1/gol/CMakeFiles/conway.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conway.dir/depend

