# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/peter/CLionProjects/Taller sockets"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/peter/CLionProjects/Taller sockets/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled1.dir/flags.make

CMakeFiles/untitled1.dir/main.cpp.o: CMakeFiles/untitled1.dir/flags.make
CMakeFiles/untitled1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/peter/CLionProjects/Taller sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled1.dir/main.cpp.o -c "/home/peter/CLionProjects/Taller sockets/main.cpp"

CMakeFiles/untitled1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/CLionProjects/Taller sockets/main.cpp" > CMakeFiles/untitled1.dir/main.cpp.i

CMakeFiles/untitled1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/CLionProjects/Taller sockets/main.cpp" -o CMakeFiles/untitled1.dir/main.cpp.s

CMakeFiles/untitled1.dir/Server.cpp.o: CMakeFiles/untitled1.dir/flags.make
CMakeFiles/untitled1.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/peter/CLionProjects/Taller sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/untitled1.dir/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled1.dir/Server.cpp.o -c "/home/peter/CLionProjects/Taller sockets/Server.cpp"

CMakeFiles/untitled1.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled1.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/CLionProjects/Taller sockets/Server.cpp" > CMakeFiles/untitled1.dir/Server.cpp.i

CMakeFiles/untitled1.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled1.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/CLionProjects/Taller sockets/Server.cpp" -o CMakeFiles/untitled1.dir/Server.cpp.s

CMakeFiles/untitled1.dir/Client.cpp.o: CMakeFiles/untitled1.dir/flags.make
CMakeFiles/untitled1.dir/Client.cpp.o: ../Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/peter/CLionProjects/Taller sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/untitled1.dir/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled1.dir/Client.cpp.o -c "/home/peter/CLionProjects/Taller sockets/Client.cpp"

CMakeFiles/untitled1.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled1.dir/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/CLionProjects/Taller sockets/Client.cpp" > CMakeFiles/untitled1.dir/Client.cpp.i

CMakeFiles/untitled1.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled1.dir/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/CLionProjects/Taller sockets/Client.cpp" -o CMakeFiles/untitled1.dir/Client.cpp.s

# Object files for target untitled1
untitled1_OBJECTS = \
"CMakeFiles/untitled1.dir/main.cpp.o" \
"CMakeFiles/untitled1.dir/Server.cpp.o" \
"CMakeFiles/untitled1.dir/Client.cpp.o"

# External object files for target untitled1
untitled1_EXTERNAL_OBJECTS =

../bin/untitled1: CMakeFiles/untitled1.dir/main.cpp.o
../bin/untitled1: CMakeFiles/untitled1.dir/Server.cpp.o
../bin/untitled1: CMakeFiles/untitled1.dir/Client.cpp.o
../bin/untitled1: CMakeFiles/untitled1.dir/build.make
../bin/untitled1: /usr/lib/x86_64-linux-gnu/libSDL2main.a
../bin/untitled1: /usr/lib/x86_64-linux-gnu/libSDL2.so
../bin/untitled1: CMakeFiles/untitled1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/peter/CLionProjects/Taller sockets/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/untitled1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled1.dir/build: ../bin/untitled1

.PHONY : CMakeFiles/untitled1.dir/build

CMakeFiles/untitled1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled1.dir/clean

CMakeFiles/untitled1.dir/depend:
	cd "/home/peter/CLionProjects/Taller sockets/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/peter/CLionProjects/Taller sockets" "/home/peter/CLionProjects/Taller sockets" "/home/peter/CLionProjects/Taller sockets/cmake-build-debug" "/home/peter/CLionProjects/Taller sockets/cmake-build-debug" "/home/peter/CLionProjects/Taller sockets/cmake-build-debug/CMakeFiles/untitled1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled1.dir/depend

