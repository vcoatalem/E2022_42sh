# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/xarang/E2022_42sh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xarang/E2022_42sh/tests

# Include any dependencies generated for this target.
include src/execution/CMakeFiles/test_execution_builtins.dir/depend.make

# Include the progress variables for this target.
include src/execution/CMakeFiles/test_execution_builtins.dir/progress.make

# Include the compile flags for this target's objects.
include src/execution/CMakeFiles/test_execution_builtins.dir/flags.make

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o: src/execution/CMakeFiles/test_execution_builtins.dir/flags.make
src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o: ../src/execution/tests/builtins/test_execution_builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o   -c /home/xarang/E2022_42sh/src/execution/tests/builtins/test_execution_builtins.c

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/tests/builtins/test_execution_builtins.c > CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.i

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/tests/builtins/test_execution_builtins.c -o CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.s

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.requires:

.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.requires

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.provides: src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/test_execution_builtins.dir/build.make src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.provides.build
.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.provides

src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.provides.build: src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o


# Object files for target test_execution_builtins
test_execution_builtins_OBJECTS = \
"CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o"

# External object files for target test_execution_builtins
test_execution_builtins_EXTERNAL_OBJECTS =

src/execution/test_execution_builtins: src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o
src/execution/test_execution_builtins: src/execution/CMakeFiles/test_execution_builtins.dir/build.make
src/execution/test_execution_builtins: src/execution/libexecution.a
src/execution/test_execution_builtins: src/ast/libast.a
src/execution/test_execution_builtins: src/variables/libvariables.a
src/execution/test_execution_builtins: src/execution/libexecution.a
src/execution/test_execution_builtins: src/ast/libast.a
src/execution/test_execution_builtins: src/variables/libvariables.a
src/execution/test_execution_builtins: src/builtins/libbuiltins.a
src/execution/test_execution_builtins: src/options/liboptions.a
src/execution/test_execution_builtins: src/expansion/libexpansion.a
src/execution/test_execution_builtins: src/hashtable/libhashtable.a
src/execution/test_execution_builtins: src/execution/CMakeFiles/test_execution_builtins.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_execution_builtins"
	cd /home/xarang/E2022_42sh/tests/src/execution && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_execution_builtins.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/execution/CMakeFiles/test_execution_builtins.dir/build: src/execution/test_execution_builtins

.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/build

src/execution/CMakeFiles/test_execution_builtins.dir/requires: src/execution/CMakeFiles/test_execution_builtins.dir/tests/builtins/test_execution_builtins.c.o.requires

.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/requires

src/execution/CMakeFiles/test_execution_builtins.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/execution && $(CMAKE_COMMAND) -P CMakeFiles/test_execution_builtins.dir/cmake_clean.cmake
.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/clean

src/execution/CMakeFiles/test_execution_builtins.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/execution /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/execution /home/xarang/E2022_42sh/tests/src/execution/CMakeFiles/test_execution_builtins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/execution/CMakeFiles/test_execution_builtins.dir/depend

