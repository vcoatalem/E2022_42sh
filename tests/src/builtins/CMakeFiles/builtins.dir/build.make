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
include src/builtins/CMakeFiles/builtins.dir/depend.make

# Include the progress variables for this target.
include src/builtins/CMakeFiles/builtins.dir/progress.make

# Include the compile flags for this target's objects.
include src/builtins/CMakeFiles/builtins.dir/flags.make

src/builtins/CMakeFiles/builtins.dir/alias.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/alias.c.o: ../src/builtins/alias.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/builtins/CMakeFiles/builtins.dir/alias.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/alias.c.o   -c /home/xarang/E2022_42sh/src/builtins/alias.c

src/builtins/CMakeFiles/builtins.dir/alias.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/alias.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/alias.c > CMakeFiles/builtins.dir/alias.c.i

src/builtins/CMakeFiles/builtins.dir/alias.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/alias.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/alias.c -o CMakeFiles/builtins.dir/alias.c.s

src/builtins/CMakeFiles/builtins.dir/alias.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/alias.c.o.requires

src/builtins/CMakeFiles/builtins.dir/alias.c.o.provides: src/builtins/CMakeFiles/builtins.dir/alias.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/alias.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/alias.c.o.provides

src/builtins/CMakeFiles/builtins.dir/alias.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/alias.c.o


src/builtins/CMakeFiles/builtins.dir/builtins.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/builtins.c.o: ../src/builtins/builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/builtins/CMakeFiles/builtins.dir/builtins.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/builtins.c.o   -c /home/xarang/E2022_42sh/src/builtins/builtins.c

src/builtins/CMakeFiles/builtins.dir/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/builtins.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/builtins.c > CMakeFiles/builtins.dir/builtins.c.i

src/builtins/CMakeFiles/builtins.dir/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/builtins.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/builtins.c -o CMakeFiles/builtins.dir/builtins.c.s

src/builtins/CMakeFiles/builtins.dir/builtins.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/builtins.c.o.requires

src/builtins/CMakeFiles/builtins.dir/builtins.c.o.provides: src/builtins/CMakeFiles/builtins.dir/builtins.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/builtins.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/builtins.c.o.provides

src/builtins/CMakeFiles/builtins.dir/builtins.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/builtins.c.o


src/builtins/CMakeFiles/builtins.dir/cd.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/cd.c.o: ../src/builtins/cd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/builtins/CMakeFiles/builtins.dir/cd.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/cd.c.o   -c /home/xarang/E2022_42sh/src/builtins/cd.c

src/builtins/CMakeFiles/builtins.dir/cd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/cd.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/cd.c > CMakeFiles/builtins.dir/cd.c.i

src/builtins/CMakeFiles/builtins.dir/cd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/cd.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/cd.c -o CMakeFiles/builtins.dir/cd.c.s

src/builtins/CMakeFiles/builtins.dir/cd.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/cd.c.o.requires

src/builtins/CMakeFiles/builtins.dir/cd.c.o.provides: src/builtins/CMakeFiles/builtins.dir/cd.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/cd.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/cd.c.o.provides

src/builtins/CMakeFiles/builtins.dir/cd.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/cd.c.o


src/builtins/CMakeFiles/builtins.dir/export.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/export.c.o: ../src/builtins/export.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/builtins/CMakeFiles/builtins.dir/export.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/export.c.o   -c /home/xarang/E2022_42sh/src/builtins/export.c

src/builtins/CMakeFiles/builtins.dir/export.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/export.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/export.c > CMakeFiles/builtins.dir/export.c.i

src/builtins/CMakeFiles/builtins.dir/export.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/export.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/export.c -o CMakeFiles/builtins.dir/export.c.s

src/builtins/CMakeFiles/builtins.dir/export.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/export.c.o.requires

src/builtins/CMakeFiles/builtins.dir/export.c.o.provides: src/builtins/CMakeFiles/builtins.dir/export.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/export.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/export.c.o.provides

src/builtins/CMakeFiles/builtins.dir/export.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/export.c.o


src/builtins/CMakeFiles/builtins.dir/history.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/history.c.o: ../src/builtins/history.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/builtins/CMakeFiles/builtins.dir/history.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/history.c.o   -c /home/xarang/E2022_42sh/src/builtins/history.c

src/builtins/CMakeFiles/builtins.dir/history.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/history.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/history.c > CMakeFiles/builtins.dir/history.c.i

src/builtins/CMakeFiles/builtins.dir/history.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/history.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/history.c -o CMakeFiles/builtins.dir/history.c.s

src/builtins/CMakeFiles/builtins.dir/history.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/history.c.o.requires

src/builtins/CMakeFiles/builtins.dir/history.c.o.provides: src/builtins/CMakeFiles/builtins.dir/history.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/history.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/history.c.o.provides

src/builtins/CMakeFiles/builtins.dir/history.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/history.c.o


src/builtins/CMakeFiles/builtins.dir/shopt.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/shopt.c.o: ../src/builtins/shopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/builtins/CMakeFiles/builtins.dir/shopt.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/shopt.c.o   -c /home/xarang/E2022_42sh/src/builtins/shopt.c

src/builtins/CMakeFiles/builtins.dir/shopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/shopt.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/shopt.c > CMakeFiles/builtins.dir/shopt.c.i

src/builtins/CMakeFiles/builtins.dir/shopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/shopt.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/shopt.c -o CMakeFiles/builtins.dir/shopt.c.s

src/builtins/CMakeFiles/builtins.dir/shopt.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/shopt.c.o.requires

src/builtins/CMakeFiles/builtins.dir/shopt.c.o.provides: src/builtins/CMakeFiles/builtins.dir/shopt.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/shopt.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/shopt.c.o.provides

src/builtins/CMakeFiles/builtins.dir/shopt.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/shopt.c.o


src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o: src/builtins/CMakeFiles/builtins.dir/flags.make
src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o: ../src/builtins/break_continue_exit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/break_continue_exit.c.o   -c /home/xarang/E2022_42sh/src/builtins/break_continue_exit.c

src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/break_continue_exit.c.i"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/builtins/break_continue_exit.c > CMakeFiles/builtins.dir/break_continue_exit.c.i

src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/break_continue_exit.c.s"
	cd /home/xarang/E2022_42sh/tests/src/builtins && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/builtins/break_continue_exit.c -o CMakeFiles/builtins.dir/break_continue_exit.c.s

src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.requires:

.PHONY : src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.requires

src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.provides: src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.requires
	$(MAKE) -f src/builtins/CMakeFiles/builtins.dir/build.make src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.provides.build
.PHONY : src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.provides

src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.provides.build: src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o


# Object files for target builtins
builtins_OBJECTS = \
"CMakeFiles/builtins.dir/alias.c.o" \
"CMakeFiles/builtins.dir/builtins.c.o" \
"CMakeFiles/builtins.dir/cd.c.o" \
"CMakeFiles/builtins.dir/export.c.o" \
"CMakeFiles/builtins.dir/history.c.o" \
"CMakeFiles/builtins.dir/shopt.c.o" \
"CMakeFiles/builtins.dir/break_continue_exit.c.o"

# External object files for target builtins
builtins_EXTERNAL_OBJECTS =

src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/alias.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/builtins.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/cd.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/export.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/history.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/shopt.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/build.make
src/builtins/libbuiltins.a: src/builtins/CMakeFiles/builtins.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libbuiltins.a"
	cd /home/xarang/E2022_42sh/tests/src/builtins && $(CMAKE_COMMAND) -P CMakeFiles/builtins.dir/cmake_clean_target.cmake
	cd /home/xarang/E2022_42sh/tests/src/builtins && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/builtins.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/builtins/CMakeFiles/builtins.dir/build: src/builtins/libbuiltins.a

.PHONY : src/builtins/CMakeFiles/builtins.dir/build

src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/alias.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/builtins.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/cd.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/export.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/history.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/shopt.c.o.requires
src/builtins/CMakeFiles/builtins.dir/requires: src/builtins/CMakeFiles/builtins.dir/break_continue_exit.c.o.requires

.PHONY : src/builtins/CMakeFiles/builtins.dir/requires

src/builtins/CMakeFiles/builtins.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/builtins && $(CMAKE_COMMAND) -P CMakeFiles/builtins.dir/cmake_clean.cmake
.PHONY : src/builtins/CMakeFiles/builtins.dir/clean

src/builtins/CMakeFiles/builtins.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/builtins /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/builtins /home/xarang/E2022_42sh/tests/src/builtins/CMakeFiles/builtins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/builtins/CMakeFiles/builtins.dir/depend
