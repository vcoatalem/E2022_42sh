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
include src/parser/CMakeFiles/test_grammar_basic.dir/depend.make

# Include the progress variables for this target.
include src/parser/CMakeFiles/test_grammar_basic.dir/progress.make

# Include the compile flags for this target's objects.
include src/parser/CMakeFiles/test_grammar_basic.dir/flags.make

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o: src/parser/CMakeFiles/test_grammar_basic.dir/flags.make
src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o: ../src/parser/tests/test_grammar_basic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o"
	cd /home/xarang/E2022_42sh/tests/src/parser && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o   -c /home/xarang/E2022_42sh/src/parser/tests/test_grammar_basic.c

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.i"
	cd /home/xarang/E2022_42sh/tests/src/parser && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/parser/tests/test_grammar_basic.c > CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.i

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.s"
	cd /home/xarang/E2022_42sh/tests/src/parser && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/parser/tests/test_grammar_basic.c -o CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.s

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.requires:

.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.requires

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.provides: src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.requires
	$(MAKE) -f src/parser/CMakeFiles/test_grammar_basic.dir/build.make src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.provides.build
.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.provides

src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.provides.build: src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o


# Object files for target test_grammar_basic
test_grammar_basic_OBJECTS = \
"CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o"

# External object files for target test_grammar_basic
test_grammar_basic_EXTERNAL_OBJECTS =

src/parser/test_grammar_basic: src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o
src/parser/test_grammar_basic: src/parser/CMakeFiles/test_grammar_basic.dir/build.make
src/parser/test_grammar_basic: src/parser/libparser.a
src/parser/test_grammar_basic: src/lexer/liblexer.a
src/parser/test_grammar_basic: src/ast/libast.a
src/parser/test_grammar_basic: src/execution/libexecution.a
src/parser/test_grammar_basic: src/variables/libvariables.a
src/parser/test_grammar_basic: src/ast/libast.a
src/parser/test_grammar_basic: src/execution/libexecution.a
src/parser/test_grammar_basic: src/variables/libvariables.a
src/parser/test_grammar_basic: src/expansion/libexpansion.a
src/parser/test_grammar_basic: src/builtins/libbuiltins.a
src/parser/test_grammar_basic: src/options/liboptions.a
src/parser/test_grammar_basic: src/hashtable/libhashtable.a
src/parser/test_grammar_basic: src/parser/CMakeFiles/test_grammar_basic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_grammar_basic"
	cd /home/xarang/E2022_42sh/tests/src/parser && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_grammar_basic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/parser/CMakeFiles/test_grammar_basic.dir/build: src/parser/test_grammar_basic

.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/build

src/parser/CMakeFiles/test_grammar_basic.dir/requires: src/parser/CMakeFiles/test_grammar_basic.dir/tests/test_grammar_basic.c.o.requires

.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/requires

src/parser/CMakeFiles/test_grammar_basic.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/parser && $(CMAKE_COMMAND) -P CMakeFiles/test_grammar_basic.dir/cmake_clean.cmake
.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/clean

src/parser/CMakeFiles/test_grammar_basic.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/parser /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/parser /home/xarang/E2022_42sh/tests/src/parser/CMakeFiles/test_grammar_basic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/parser/CMakeFiles/test_grammar_basic.dir/depend

