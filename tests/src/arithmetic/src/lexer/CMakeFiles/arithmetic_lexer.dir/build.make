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
include src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/depend.make

# Include the progress variables for this target.
include src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/progress.make

# Include the compile flags for this target's objects.
include src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/flags.make

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/flags.make
src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o: ../src/arithmetic/src/lexer/lexer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/arithmetic_lexer.dir/lexer.c.o   -c /home/xarang/E2022_42sh/src/arithmetic/src/lexer/lexer.c

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/arithmetic_lexer.dir/lexer.c.i"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/arithmetic/src/lexer/lexer.c > CMakeFiles/arithmetic_lexer.dir/lexer.c.i

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/arithmetic_lexer.dir/lexer.c.s"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/arithmetic/src/lexer/lexer.c -o CMakeFiles/arithmetic_lexer.dir/lexer.c.s

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.requires:

.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.requires

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.provides: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.requires
	$(MAKE) -f src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/build.make src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.provides.build
.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.provides

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.provides.build: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o


src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/flags.make
src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o: ../src/arithmetic/src/lexer/token.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/arithmetic_lexer.dir/token.c.o   -c /home/xarang/E2022_42sh/src/arithmetic/src/lexer/token.c

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/arithmetic_lexer.dir/token.c.i"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/arithmetic/src/lexer/token.c > CMakeFiles/arithmetic_lexer.dir/token.c.i

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/arithmetic_lexer.dir/token.c.s"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/arithmetic/src/lexer/token.c -o CMakeFiles/arithmetic_lexer.dir/token.c.s

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.requires:

.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.requires

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.provides: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.requires
	$(MAKE) -f src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/build.make src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.provides.build
.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.provides

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.provides.build: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o


# Object files for target arithmetic_lexer
arithmetic_lexer_OBJECTS = \
"CMakeFiles/arithmetic_lexer.dir/lexer.c.o" \
"CMakeFiles/arithmetic_lexer.dir/token.c.o"

# External object files for target arithmetic_lexer
arithmetic_lexer_EXTERNAL_OBJECTS =

src/arithmetic/src/lexer/libarithmetic_lexer.a: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o
src/arithmetic/src/lexer/libarithmetic_lexer.a: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o
src/arithmetic/src/lexer/libarithmetic_lexer.a: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/build.make
src/arithmetic/src/lexer/libarithmetic_lexer.a: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libarithmetic_lexer.a"
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && $(CMAKE_COMMAND) -P CMakeFiles/arithmetic_lexer.dir/cmake_clean_target.cmake
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arithmetic_lexer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/build: src/arithmetic/src/lexer/libarithmetic_lexer.a

.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/build

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/requires: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/lexer.c.o.requires
src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/requires: src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/token.c.o.requires

.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/requires

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer && $(CMAKE_COMMAND) -P CMakeFiles/arithmetic_lexer.dir/cmake_clean.cmake
.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/clean

src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/arithmetic/src/lexer /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer /home/xarang/E2022_42sh/tests/src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/arithmetic/src/lexer/CMakeFiles/arithmetic_lexer.dir/depend

