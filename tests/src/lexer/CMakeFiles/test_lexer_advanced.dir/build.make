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
include src/lexer/CMakeFiles/test_lexer_advanced.dir/depend.make

# Include the progress variables for this target.
include src/lexer/CMakeFiles/test_lexer_advanced.dir/progress.make

# Include the compile flags for this target's objects.
include src/lexer/CMakeFiles/test_lexer_advanced.dir/flags.make

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o: src/lexer/CMakeFiles/test_lexer_advanced.dir/flags.make
src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o: ../src/lexer/tests/test_advanced.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o"
	cd /home/xarang/E2022_42sh/tests/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o   -c /home/xarang/E2022_42sh/src/lexer/tests/test_advanced.c

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.i"
	cd /home/xarang/E2022_42sh/tests/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/lexer/tests/test_advanced.c > CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.i

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.s"
	cd /home/xarang/E2022_42sh/tests/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/lexer/tests/test_advanced.c -o CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.s

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.requires:

.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.requires

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.provides: src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.requires
	$(MAKE) -f src/lexer/CMakeFiles/test_lexer_advanced.dir/build.make src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.provides.build
.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.provides

src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.provides.build: src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o


# Object files for target test_lexer_advanced
test_lexer_advanced_OBJECTS = \
"CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o"

# External object files for target test_lexer_advanced
test_lexer_advanced_EXTERNAL_OBJECTS =

src/lexer/test_lexer_advanced: src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o
src/lexer/test_lexer_advanced: src/lexer/CMakeFiles/test_lexer_advanced.dir/build.make
src/lexer/test_lexer_advanced: src/lexer/liblexer.a
src/lexer/test_lexer_advanced: src/lexer/CMakeFiles/test_lexer_advanced.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_lexer_advanced"
	cd /home/xarang/E2022_42sh/tests/src/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_lexer_advanced.dir/link.txt --verbose=$(VERBOSE)
	cd /home/xarang/E2022_42sh/tests/src/lexer && /bin/sh /home/xarang/E2022_42sh/src/lexer/run_tests.sh /home/xarang/E2022_42sh/build/src/lexer/test_lexer_advanced

# Rule to build all files generated by this target.
src/lexer/CMakeFiles/test_lexer_advanced.dir/build: src/lexer/test_lexer_advanced

.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/build

src/lexer/CMakeFiles/test_lexer_advanced.dir/requires: src/lexer/CMakeFiles/test_lexer_advanced.dir/tests/test_advanced.c.o.requires

.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/requires

src/lexer/CMakeFiles/test_lexer_advanced.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/lexer && $(CMAKE_COMMAND) -P CMakeFiles/test_lexer_advanced.dir/cmake_clean.cmake
.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/clean

src/lexer/CMakeFiles/test_lexer_advanced.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/lexer /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/lexer /home/xarang/E2022_42sh/tests/src/lexer/CMakeFiles/test_lexer_advanced.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lexer/CMakeFiles/test_lexer_advanced.dir/depend
