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
include src/ast/CMakeFiles/ast.dir/depend.make

# Include the progress variables for this target.
include src/ast/CMakeFiles/ast.dir/progress.make

# Include the compile flags for this target's objects.
include src/ast/CMakeFiles/ast.dir/flags.make

src/ast/CMakeFiles/ast.dir/ast.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast.c.o: ../src/ast/ast.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/ast/CMakeFiles/ast.dir/ast.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast.c.o   -c /home/xarang/E2022_42sh/src/ast/ast.c

src/ast/CMakeFiles/ast.dir/ast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/ast.c > CMakeFiles/ast.dir/ast.c.i

src/ast/CMakeFiles/ast.dir/ast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/ast.c -o CMakeFiles/ast.dir/ast.c.s

src/ast/CMakeFiles/ast.dir/ast.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/ast.c.o.requires

src/ast/CMakeFiles/ast.dir/ast.c.o.provides: src/ast/CMakeFiles/ast.dir/ast.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/ast.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/ast.c.o.provides

src/ast/CMakeFiles/ast.dir/ast.c.o.provides.build: src/ast/CMakeFiles/ast.dir/ast.c.o


src/ast/CMakeFiles/ast.dir/ast_utils.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_utils.c.o: ../src/ast/ast_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/ast/CMakeFiles/ast.dir/ast_utils.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_utils.c.o   -c /home/xarang/E2022_42sh/src/ast/ast_utils.c

src/ast/CMakeFiles/ast.dir/ast_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_utils.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/ast_utils.c > CMakeFiles/ast.dir/ast_utils.c.i

src/ast/CMakeFiles/ast.dir/ast_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_utils.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/ast_utils.c -o CMakeFiles/ast.dir/ast_utils.c.s

src/ast/CMakeFiles/ast.dir/ast_utils.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/ast_utils.c.o.requires

src/ast/CMakeFiles/ast.dir/ast_utils.c.o.provides: src/ast/CMakeFiles/ast.dir/ast_utils.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/ast_utils.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/ast_utils.c.o.provides

src/ast/CMakeFiles/ast.dir/ast_utils.c.o.provides.build: src/ast/CMakeFiles/ast.dir/ast_utils.c.o


src/ast/CMakeFiles/ast.dir/ast_print.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_print.c.o: ../src/ast/ast_print.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/ast/CMakeFiles/ast.dir/ast_print.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_print.c.o   -c /home/xarang/E2022_42sh/src/ast/ast_print.c

src/ast/CMakeFiles/ast.dir/ast_print.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_print.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/ast_print.c > CMakeFiles/ast.dir/ast_print.c.i

src/ast/CMakeFiles/ast.dir/ast_print.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_print.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/ast_print.c -o CMakeFiles/ast.dir/ast_print.c.s

src/ast/CMakeFiles/ast.dir/ast_print.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/ast_print.c.o.requires

src/ast/CMakeFiles/ast.dir/ast_print.c.o.provides: src/ast/CMakeFiles/ast.dir/ast_print.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/ast_print.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/ast_print.c.o.provides

src/ast/CMakeFiles/ast.dir/ast_print.c.o.provides.build: src/ast/CMakeFiles/ast.dir/ast_print.c.o


src/ast/CMakeFiles/ast.dir/ast_execute.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_execute.c.o: ../src/ast/ast_execute.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/ast/CMakeFiles/ast.dir/ast_execute.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_execute.c.o   -c /home/xarang/E2022_42sh/src/ast/ast_execute.c

src/ast/CMakeFiles/ast.dir/ast_execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_execute.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/ast_execute.c > CMakeFiles/ast.dir/ast_execute.c.i

src/ast/CMakeFiles/ast.dir/ast_execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_execute.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/ast_execute.c -o CMakeFiles/ast.dir/ast_execute.c.s

src/ast/CMakeFiles/ast.dir/ast_execute.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/ast_execute.c.o.requires

src/ast/CMakeFiles/ast.dir/ast_execute.c.o.provides: src/ast/CMakeFiles/ast.dir/ast_execute.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/ast_execute.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/ast_execute.c.o.provides

src/ast/CMakeFiles/ast.dir/ast_execute.c.o.provides.build: src/ast/CMakeFiles/ast.dir/ast_execute.c.o


src/ast/CMakeFiles/ast.dir/builders/arglist.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/builders/arglist.c.o: ../src/ast/builders/arglist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/ast/CMakeFiles/ast.dir/builders/arglist.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/builders/arglist.c.o   -c /home/xarang/E2022_42sh/src/ast/builders/arglist.c

src/ast/CMakeFiles/ast.dir/builders/arglist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/builders/arglist.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/builders/arglist.c > CMakeFiles/ast.dir/builders/arglist.c.i

src/ast/CMakeFiles/ast.dir/builders/arglist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/builders/arglist.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/builders/arglist.c -o CMakeFiles/ast.dir/builders/arglist.c.s

src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.requires

src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.provides: src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.provides

src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.provides.build: src/ast/CMakeFiles/ast.dir/builders/arglist.c.o


src/ast/CMakeFiles/ast.dir/builders/redirections.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/builders/redirections.c.o: ../src/ast/builders/redirections.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/ast/CMakeFiles/ast.dir/builders/redirections.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/builders/redirections.c.o   -c /home/xarang/E2022_42sh/src/ast/builders/redirections.c

src/ast/CMakeFiles/ast.dir/builders/redirections.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/builders/redirections.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/builders/redirections.c > CMakeFiles/ast.dir/builders/redirections.c.i

src/ast/CMakeFiles/ast.dir/builders/redirections.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/builders/redirections.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/builders/redirections.c -o CMakeFiles/ast.dir/builders/redirections.c.s

src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.requires

src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.provides: src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.provides

src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.provides.build: src/ast/CMakeFiles/ast.dir/builders/redirections.c.o


src/ast/CMakeFiles/ast.dir/builders/commands.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/builders/commands.c.o: ../src/ast/builders/commands.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/ast/CMakeFiles/ast.dir/builders/commands.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/builders/commands.c.o   -c /home/xarang/E2022_42sh/src/ast/builders/commands.c

src/ast/CMakeFiles/ast.dir/builders/commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/builders/commands.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/builders/commands.c > CMakeFiles/ast.dir/builders/commands.c.i

src/ast/CMakeFiles/ast.dir/builders/commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/builders/commands.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/builders/commands.c -o CMakeFiles/ast.dir/builders/commands.c.s

src/ast/CMakeFiles/ast.dir/builders/commands.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/builders/commands.c.o.requires

src/ast/CMakeFiles/ast.dir/builders/commands.c.o.provides: src/ast/CMakeFiles/ast.dir/builders/commands.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/builders/commands.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/builders/commands.c.o.provides

src/ast/CMakeFiles/ast.dir/builders/commands.c.o.provides.build: src/ast/CMakeFiles/ast.dir/builders/commands.c.o


src/ast/CMakeFiles/ast.dir/handlers/list.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/list.c.o: ../src/ast/handlers/list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/ast/CMakeFiles/ast.dir/handlers/list.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/list.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/list.c

src/ast/CMakeFiles/ast.dir/handlers/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/list.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/list.c > CMakeFiles/ast.dir/handlers/list.c.i

src/ast/CMakeFiles/ast.dir/handlers/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/list.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/list.c -o CMakeFiles/ast.dir/handlers/list.c.s

src/ast/CMakeFiles/ast.dir/handlers/list.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/list.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/list.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/list.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/list.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/list.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/list.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/list.c.o


src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o: ../src/ast/handlers/and_or.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/and_or.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/and_or.c

src/ast/CMakeFiles/ast.dir/handlers/and_or.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/and_or.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/and_or.c > CMakeFiles/ast.dir/handlers/and_or.c.i

src/ast/CMakeFiles/ast.dir/handlers/and_or.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/and_or.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/and_or.c -o CMakeFiles/ast.dir/handlers/and_or.c.s

src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o


src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o: ../src/ast/handlers/pipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/pipe.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/pipe.c

src/ast/CMakeFiles/ast.dir/handlers/pipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/pipe.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/pipe.c > CMakeFiles/ast.dir/handlers/pipe.c.i

src/ast/CMakeFiles/ast.dir/handlers/pipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/pipe.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/pipe.c -o CMakeFiles/ast.dir/handlers/pipe.c.s

src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o


src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o: ../src/ast/handlers/if_then.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/if_then.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/if_then.c

src/ast/CMakeFiles/ast.dir/handlers/if_then.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/if_then.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/if_then.c > CMakeFiles/ast.dir/handlers/if_then.c.i

src/ast/CMakeFiles/ast.dir/handlers/if_then.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/if_then.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/if_then.c -o CMakeFiles/ast.dir/handlers/if_then.c.s

src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o


src/ast/CMakeFiles/ast.dir/handlers/for.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/for.c.o: ../src/ast/handlers/for.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object src/ast/CMakeFiles/ast.dir/handlers/for.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/for.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/for.c

src/ast/CMakeFiles/ast.dir/handlers/for.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/for.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/for.c > CMakeFiles/ast.dir/handlers/for.c.i

src/ast/CMakeFiles/ast.dir/handlers/for.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/for.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/for.c -o CMakeFiles/ast.dir/handlers/for.c.s

src/ast/CMakeFiles/ast.dir/handlers/for.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/for.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/for.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/for.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/for.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/for.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/for.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/for.c.o


src/ast/CMakeFiles/ast.dir/handlers/until.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/until.c.o: ../src/ast/handlers/until.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object src/ast/CMakeFiles/ast.dir/handlers/until.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/until.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/until.c

src/ast/CMakeFiles/ast.dir/handlers/until.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/until.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/until.c > CMakeFiles/ast.dir/handlers/until.c.i

src/ast/CMakeFiles/ast.dir/handlers/until.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/until.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/until.c -o CMakeFiles/ast.dir/handlers/until.c.s

src/ast/CMakeFiles/ast.dir/handlers/until.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/until.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/until.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/until.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/until.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/until.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/until.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/until.c.o


src/ast/CMakeFiles/ast.dir/handlers/while.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/while.c.o: ../src/ast/handlers/while.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object src/ast/CMakeFiles/ast.dir/handlers/while.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/while.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/while.c

src/ast/CMakeFiles/ast.dir/handlers/while.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/while.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/while.c > CMakeFiles/ast.dir/handlers/while.c.i

src/ast/CMakeFiles/ast.dir/handlers/while.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/while.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/while.c -o CMakeFiles/ast.dir/handlers/while.c.s

src/ast/CMakeFiles/ast.dir/handlers/while.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/while.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/while.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/while.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/while.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/while.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/while.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/while.c.o


src/ast/CMakeFiles/ast.dir/handlers/case.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/case.c.o: ../src/ast/handlers/case.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object src/ast/CMakeFiles/ast.dir/handlers/case.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/case.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/case.c

src/ast/CMakeFiles/ast.dir/handlers/case.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/case.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/case.c > CMakeFiles/ast.dir/handlers/case.c.i

src/ast/CMakeFiles/ast.dir/handlers/case.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/case.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/case.c -o CMakeFiles/ast.dir/handlers/case.c.s

src/ast/CMakeFiles/ast.dir/handlers/case.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/case.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/case.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/case.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/case.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/case.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/case.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/case.c.o


src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o: ../src/ast/handlers/funcdec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/funcdec.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/funcdec.c

src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/funcdec.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/funcdec.c > CMakeFiles/ast.dir/handlers/funcdec.c.i

src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/funcdec.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/funcdec.c -o CMakeFiles/ast.dir/handlers/funcdec.c.s

src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o


src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o: ../src/ast/handlers/vardec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/handlers/vardec.c.o   -c /home/xarang/E2022_42sh/src/ast/handlers/vardec.c

src/ast/CMakeFiles/ast.dir/handlers/vardec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/handlers/vardec.c.i"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xarang/E2022_42sh/src/ast/handlers/vardec.c > CMakeFiles/ast.dir/handlers/vardec.c.i

src/ast/CMakeFiles/ast.dir/handlers/vardec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/handlers/vardec.c.s"
	cd /home/xarang/E2022_42sh/tests/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xarang/E2022_42sh/src/ast/handlers/vardec.c -o CMakeFiles/ast.dir/handlers/vardec.c.s

src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.requires:

.PHONY : src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.requires

src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.provides: src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.requires
	$(MAKE) -f src/ast/CMakeFiles/ast.dir/build.make src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.provides.build
.PHONY : src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.provides

src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.provides.build: src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o


# Object files for target ast
ast_OBJECTS = \
"CMakeFiles/ast.dir/ast.c.o" \
"CMakeFiles/ast.dir/ast_utils.c.o" \
"CMakeFiles/ast.dir/ast_print.c.o" \
"CMakeFiles/ast.dir/ast_execute.c.o" \
"CMakeFiles/ast.dir/builders/arglist.c.o" \
"CMakeFiles/ast.dir/builders/redirections.c.o" \
"CMakeFiles/ast.dir/builders/commands.c.o" \
"CMakeFiles/ast.dir/handlers/list.c.o" \
"CMakeFiles/ast.dir/handlers/and_or.c.o" \
"CMakeFiles/ast.dir/handlers/pipe.c.o" \
"CMakeFiles/ast.dir/handlers/if_then.c.o" \
"CMakeFiles/ast.dir/handlers/for.c.o" \
"CMakeFiles/ast.dir/handlers/until.c.o" \
"CMakeFiles/ast.dir/handlers/while.c.o" \
"CMakeFiles/ast.dir/handlers/case.c.o" \
"CMakeFiles/ast.dir/handlers/funcdec.c.o" \
"CMakeFiles/ast.dir/handlers/vardec.c.o"

# External object files for target ast
ast_EXTERNAL_OBJECTS =

src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_utils.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_print.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_execute.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/builders/arglist.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/builders/redirections.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/builders/commands.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/list.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/for.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/until.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/while.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/case.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/build.make
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xarang/E2022_42sh/tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking C static library libast.a"
	cd /home/xarang/E2022_42sh/tests/src/ast && $(CMAKE_COMMAND) -P CMakeFiles/ast.dir/cmake_clean_target.cmake
	cd /home/xarang/E2022_42sh/tests/src/ast && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ast/CMakeFiles/ast.dir/build: src/ast/libast.a

.PHONY : src/ast/CMakeFiles/ast.dir/build

src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/ast.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/ast_utils.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/ast_print.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/ast_execute.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/builders/arglist.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/builders/redirections.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/builders/commands.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/list.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/and_or.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/pipe.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/if_then.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/for.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/until.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/while.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/case.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/funcdec.c.o.requires
src/ast/CMakeFiles/ast.dir/requires: src/ast/CMakeFiles/ast.dir/handlers/vardec.c.o.requires

.PHONY : src/ast/CMakeFiles/ast.dir/requires

src/ast/CMakeFiles/ast.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/ast && $(CMAKE_COMMAND) -P CMakeFiles/ast.dir/cmake_clean.cmake
.PHONY : src/ast/CMakeFiles/ast.dir/clean

src/ast/CMakeFiles/ast.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/ast /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/ast /home/xarang/E2022_42sh/tests/src/ast/CMakeFiles/ast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ast/CMakeFiles/ast.dir/depend
