# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /snap/clion/44/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/44/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vdberg/CLionProjects/vector_model

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vdberg/CLionProjects/vector_model/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/vector_model.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vector_model.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vector_model.dir/flags.make

CMakeFiles/vector_model.dir/indexer/indexer.cpp.o: CMakeFiles/vector_model.dir/flags.make
CMakeFiles/vector_model.dir/indexer/indexer.cpp.o: ../indexer/indexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vector_model.dir/indexer/indexer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vector_model.dir/indexer/indexer.cpp.o -c /home/vdberg/CLionProjects/vector_model/indexer/indexer.cpp

CMakeFiles/vector_model.dir/indexer/indexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vector_model.dir/indexer/indexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vdberg/CLionProjects/vector_model/indexer/indexer.cpp > CMakeFiles/vector_model.dir/indexer/indexer.cpp.i

CMakeFiles/vector_model.dir/indexer/indexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vector_model.dir/indexer/indexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vdberg/CLionProjects/vector_model/indexer/indexer.cpp -o CMakeFiles/vector_model.dir/indexer/indexer.cpp.s

CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o: CMakeFiles/vector_model.dir/flags.make
CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o: ../vector_model/vector_model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o -c /home/vdberg/CLionProjects/vector_model/vector_model/vector_model.cpp

CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vdberg/CLionProjects/vector_model/vector_model/vector_model.cpp > CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.i

CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vdberg/CLionProjects/vector_model/vector_model/vector_model.cpp -o CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.s

CMakeFiles/vector_model.dir/main.cpp.o: CMakeFiles/vector_model.dir/flags.make
CMakeFiles/vector_model.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vector_model.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vector_model.dir/main.cpp.o -c /home/vdberg/CLionProjects/vector_model/main.cpp

CMakeFiles/vector_model.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vector_model.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vdberg/CLionProjects/vector_model/main.cpp > CMakeFiles/vector_model.dir/main.cpp.i

CMakeFiles/vector_model.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vector_model.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vdberg/CLionProjects/vector_model/main.cpp -o CMakeFiles/vector_model.dir/main.cpp.s

CMakeFiles/vector_model.dir/wand/Wand.cpp.o: CMakeFiles/vector_model.dir/flags.make
CMakeFiles/vector_model.dir/wand/Wand.cpp.o: ../wand/Wand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/vector_model.dir/wand/Wand.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vector_model.dir/wand/Wand.cpp.o -c /home/vdberg/CLionProjects/vector_model/wand/Wand.cpp

CMakeFiles/vector_model.dir/wand/Wand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vector_model.dir/wand/Wand.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vdberg/CLionProjects/vector_model/wand/Wand.cpp > CMakeFiles/vector_model.dir/wand/Wand.cpp.i

CMakeFiles/vector_model.dir/wand/Wand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vector_model.dir/wand/Wand.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vdberg/CLionProjects/vector_model/wand/Wand.cpp -o CMakeFiles/vector_model.dir/wand/Wand.cpp.s

CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o: CMakeFiles/vector_model.dir/flags.make
CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o: ../wand/MinHeap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o -c /home/vdberg/CLionProjects/vector_model/wand/MinHeap.cpp

CMakeFiles/vector_model.dir/wand/MinHeap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vector_model.dir/wand/MinHeap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vdberg/CLionProjects/vector_model/wand/MinHeap.cpp > CMakeFiles/vector_model.dir/wand/MinHeap.cpp.i

CMakeFiles/vector_model.dir/wand/MinHeap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vector_model.dir/wand/MinHeap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vdberg/CLionProjects/vector_model/wand/MinHeap.cpp -o CMakeFiles/vector_model.dir/wand/MinHeap.cpp.s

# Object files for target vector_model
vector_model_OBJECTS = \
"CMakeFiles/vector_model.dir/indexer/indexer.cpp.o" \
"CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o" \
"CMakeFiles/vector_model.dir/main.cpp.o" \
"CMakeFiles/vector_model.dir/wand/Wand.cpp.o" \
"CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o"

# External object files for target vector_model
vector_model_EXTERNAL_OBJECTS =

vector_model: CMakeFiles/vector_model.dir/indexer/indexer.cpp.o
vector_model: CMakeFiles/vector_model.dir/vector_model/vector_model.cpp.o
vector_model: CMakeFiles/vector_model.dir/main.cpp.o
vector_model: CMakeFiles/vector_model.dir/wand/Wand.cpp.o
vector_model: CMakeFiles/vector_model.dir/wand/MinHeap.cpp.o
vector_model: CMakeFiles/vector_model.dir/build.make
vector_model: CMakeFiles/vector_model.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable vector_model"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vector_model.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vector_model.dir/build: vector_model

.PHONY : CMakeFiles/vector_model.dir/build

CMakeFiles/vector_model.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vector_model.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vector_model.dir/clean

CMakeFiles/vector_model.dir/depend:
	cd /home/vdberg/CLionProjects/vector_model/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vdberg/CLionProjects/vector_model /home/vdberg/CLionProjects/vector_model /home/vdberg/CLionProjects/vector_model/cmake-build-debug /home/vdberg/CLionProjects/vector_model/cmake-build-debug /home/vdberg/CLionProjects/vector_model/cmake-build-debug/CMakeFiles/vector_model.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vector_model.dir/depend
