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
include src/execution/CMakeFiles/execution.dir/depend.make

# Include the progress variables for this target.
include src/execution/CMakeFiles/execution.dir/progress.make

# Include the compile flags for this target's objects.
include src/execution/CMakeFiles/execution.dir/flags.make

src/execution/CMakeFiles/execution.dir/command.c.o: src/execution/CMakeFiles/execution.dir/flags.make
src/execution/CMakeFiles/execution.dir/command.c.o: ../src/execution/command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/execution/CMakeFiles/execution.dir/command.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/execution.dir/command.c.o   -c /home/xarang/E2022_42sh/src/execution/command.c

src/execution/CMakeFiles/execution.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execution.dir/command.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/command.c > CMakeFiles/execution.dir/command.c.i

src/execution/CMakeFiles/execution.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execution.dir/command.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/command.c -o CMakeFiles/execution.dir/command.c.s

src/execution/CMakeFiles/execution.dir/command.c.o.requires:

.PHONY : src/execution/CMakeFiles/execution.dir/command.c.o.requires

src/execution/CMakeFiles/execution.dir/command.c.o.provides: src/execution/CMakeFiles/execution.dir/command.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/execution.dir/build.make src/execution/CMakeFiles/execution.dir/command.c.o.provides.build
.PHONY : src/execution/CMakeFiles/execution.dir/command.c.o.provides

src/execution/CMakeFiles/execution.dir/command.c.o.provides.build: src/execution/CMakeFiles/execution.dir/command.c.o


src/execution/CMakeFiles/execution.dir/pipe.c.o: src/execution/CMakeFiles/execution.dir/flags.make
src/execution/CMakeFiles/execution.dir/pipe.c.o: ../src/execution/pipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/execution/CMakeFiles/execution.dir/pipe.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/execution.dir/pipe.c.o   -c /home/xarang/E2022_42sh/src/execution/pipe.c

src/execution/CMakeFiles/execution.dir/pipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execution.dir/pipe.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/pipe.c > CMakeFiles/execution.dir/pipe.c.i

src/execution/CMakeFiles/execution.dir/pipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execution.dir/pipe.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/pipe.c -o CMakeFiles/execution.dir/pipe.c.s

src/execution/CMakeFiles/execution.dir/pipe.c.o.requires:

.PHONY : src/execution/CMakeFiles/execution.dir/pipe.c.o.requires

src/execution/CMakeFiles/execution.dir/pipe.c.o.provides: src/execution/CMakeFiles/execution.dir/pipe.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/execution.dir/build.make src/execution/CMakeFiles/execution.dir/pipe.c.o.provides.build
.PHONY : src/execution/CMakeFiles/execution.dir/pipe.c.o.provides

src/execution/CMakeFiles/execution.dir/pipe.c.o.provides.build: src/execution/CMakeFiles/execution.dir/pipe.c.o


src/execution/CMakeFiles/execution.dir/redirection.c.o: src/execution/CMakeFiles/execution.dir/flags.make
src/execution/CMakeFiles/execution.dir/redirection.c.o: ../src/execution/redirection.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/execution/CMakeFiles/execution.dir/redirection.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/execution.dir/redirection.c.o   -c /home/xarang/E2022_42sh/src/execution/redirection.c

src/execution/CMakeFiles/execution.dir/redirection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execution.dir/redirection.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/redirection.c > CMakeFiles/execution.dir/redirection.c.i

src/execution/CMakeFiles/execution.dir/redirection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execution.dir/redirection.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/redirection.c -o CMakeFiles/execution.dir/redirection.c.s

src/execution/CMakeFiles/execution.dir/redirection.c.o.requires:

.PHONY : src/execution/CMakeFiles/execution.dir/redirection.c.o.requires

src/execution/CMakeFiles/execution.dir/redirection.c.o.provides: src/execution/CMakeFiles/execution.dir/redirection.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/execution.dir/build.make src/execution/CMakeFiles/execution.dir/redirection.c.o.provides.build
.PHONY : src/execution/CMakeFiles/execution.dir/redirection.c.o.provides

src/execution/CMakeFiles/execution.dir/redirection.c.o.provides.build: src/execution/CMakeFiles/execution.dir/redirection.c.o


src/execution/CMakeFiles/execution.dir/apply_redirections.c.o: src/execution/CMakeFiles/execution.dir/flags.make
src/execution/CMakeFiles/execution.dir/apply_redirections.c.o: ../src/execution/apply_redirections.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/execution/CMakeFiles/execution.dir/apply_redirections.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/execution.dir/apply_redirections.c.o   -c /home/xarang/E2022_42sh/src/execution/apply_redirections.c

src/execution/CMakeFiles/execution.dir/apply_redirections.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execution.dir/apply_redirections.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/apply_redirections.c > CMakeFiles/execution.dir/apply_redirections.c.i

src/execution/CMakeFiles/execution.dir/apply_redirections.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execution.dir/apply_redirections.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/apply_redirections.c -o CMakeFiles/execution.dir/apply_redirections.c.s

src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.requires:

.PHONY : src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.requires

src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.provides: src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/execution.dir/build.make src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.provides.build
.PHONY : src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.provides

src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.provides.build: src/execution/CMakeFiles/execution.dir/apply_redirections.c.o


src/execution/CMakeFiles/execution.dir/subshell.c.o: src/execution/CMakeFiles/execution.dir/flags.make
src/execution/CMakeFiles/execution.dir/subshell.c.o: ../src/execution/subshell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/execution/CMakeFiles/execution.dir/subshell.c.o"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/execution.dir/subshell.c.o   -c /home/xarang/E2022_42sh/src/execution/subshell.c

src/execution/CMakeFiles/execution.dir/subshell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/execution.dir/subshell.c.i"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/execution/subshell.c > CMakeFiles/execution.dir/subshell.c.i

src/execution/CMakeFiles/execution.dir/subshell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/execution.dir/subshell.c.s"
	cd /home/xarang/E2022_42sh/tests/src/execution && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/execution/subshell.c -o CMakeFiles/execution.dir/subshell.c.s

src/execution/CMakeFiles/execution.dir/subshell.c.o.requires:

.PHONY : src/execution/CMakeFiles/execution.dir/subshell.c.o.requires

src/execution/CMakeFiles/execution.dir/subshell.c.o.provides: src/execution/CMakeFiles/execution.dir/subshell.c.o.requires
	$(MAKE) -f src/execution/CMakeFiles/execution.dir/build.make src/execution/CMakeFiles/execution.dir/subshell.c.o.provides.build
.PHONY : src/execution/CMakeFiles/execution.dir/subshell.c.o.provides

src/execution/CMakeFiles/execution.dir/subshell.c.o.provides.build: src/execution/CMakeFiles/execution.dir/subshell.c.o


# Object files for target execution
execution_OBJECTS = \
"CMakeFiles/execution.dir/command.c.o" \
"CMakeFiles/execution.dir/pipe.c.o" \
"CMakeFiles/execution.dir/redirection.c.o" \
"CMakeFiles/execution.dir/apply_redirections.c.o" \
"CMakeFiles/execution.dir/subshell.c.o"

# External object files for target execution
execution_EXTERNAL_OBJECTS =

src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/command.c.o
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/pipe.c.o
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/redirection.c.o
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/apply_redirections.c.o
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/subshell.c.o
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/build.make
src/execution/libexecution.a: src/execution/CMakeFiles/execution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libexecution.a"
	cd /home/xarang/E2022_42sh/tests/src/execution && $(CMAKE_COMMAND) -P CMakeFiles/execution.dir/cmake_clean_target.cmake
	cd /home/xarang/E2022_42sh/tests/src/execution && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/execution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/execution/CMakeFiles/execution.dir/build: src/execution/libexecution.a

.PHONY : src/execution/CMakeFiles/execution.dir/build

src/execution/CMakeFiles/execution.dir/requires: src/execution/CMakeFiles/execution.dir/command.c.o.requires
src/execution/CMakeFiles/execution.dir/requires: src/execution/CMakeFiles/execution.dir/pipe.c.o.requires
src/execution/CMakeFiles/execution.dir/requires: src/execution/CMakeFiles/execution.dir/redirection.c.o.requires
src/execution/CMakeFiles/execution.dir/requires: src/execution/CMakeFiles/execution.dir/apply_redirections.c.o.requires
src/execution/CMakeFiles/execution.dir/requires: src/execution/CMakeFiles/execution.dir/subshell.c.o.requires

.PHONY : src/execution/CMakeFiles/execution.dir/requires

src/execution/CMakeFiles/execution.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/execution && $(CMAKE_COMMAND) -P CMakeFiles/execution.dir/cmake_clean.cmake
.PHONY : src/execution/CMakeFiles/execution.dir/clean

src/execution/CMakeFiles/execution.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/execution /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/execution /home/xarang/E2022_42sh/tests/src/execution/CMakeFiles/execution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/execution/CMakeFiles/execution.dir/depend
