# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build

# Include any dependencies generated for this target.
include CMakeFiles/cartonet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cartonet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cartonet.dir/flags.make

CMakeFiles/cartonet.dir/tests.c.o: CMakeFiles/cartonet.dir/flags.make
CMakeFiles/cartonet.dir/tests.c.o: ../tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cartonet.dir/tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cartonet.dir/tests.c.o   -c /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/tests.c

CMakeFiles/cartonet.dir/tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cartonet.dir/tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/tests.c > CMakeFiles/cartonet.dir/tests.c.i

CMakeFiles/cartonet.dir/tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cartonet.dir/tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/tests.c -o CMakeFiles/cartonet.dir/tests.c.s

CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o: CMakeFiles/cartonet.dir/flags.make
CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o: /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o   -c /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c

CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c > CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.i

CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c -o CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.s

# Object files for target cartonet
cartonet_OBJECTS = \
"CMakeFiles/cartonet.dir/tests.c.o" \
"CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o"

# External object files for target cartonet
cartonet_EXTERNAL_OBJECTS =

cartonet: CMakeFiles/cartonet.dir/tests.c.o
cartonet: CMakeFiles/cartonet.dir/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/fonctions.c.o
cartonet: CMakeFiles/cartonet.dir/build.make
cartonet: CMakeFiles/cartonet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable cartonet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cartonet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cartonet.dir/build: cartonet

.PHONY : CMakeFiles/cartonet.dir/build

CMakeFiles/cartonet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cartonet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cartonet.dir/clean

CMakeFiles/cartonet.dir/depend:
	cd /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build /home/smil/Bureau/P3_IMSP/2nd_semestre/prepsout/cartonet/tests_unitaires/build/CMakeFiles/cartonet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cartonet.dir/depend

