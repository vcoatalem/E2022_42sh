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

# Utility rule file for builtins_check.

# Include the progress variables for this target.
include src/builtins/CMakeFiles/builtins_check.dir/progress.make

src/builtins/CMakeFiles/builtins_check: src/builtins/test_builtin_shopt


builtins_check: src/builtins/CMakeFiles/builtins_check
builtins_check: src/builtins/CMakeFiles/builtins_check.dir/build.make

.PHONY : builtins_check

# Rule to build all files generated by this target.
src/builtins/CMakeFiles/builtins_check.dir/build: builtins_check

.PHONY : src/builtins/CMakeFiles/builtins_check.dir/build

src/builtins/CMakeFiles/builtins_check.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/builtins && $(CMAKE_COMMAND) -P CMakeFiles/builtins_check.dir/cmake_clean.cmake
.PHONY : src/builtins/CMakeFiles/builtins_check.dir/clean

src/builtins/CMakeFiles/builtins_check.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/builtins /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/builtins /home/xarang/E2022_42sh/tests/src/builtins/CMakeFiles/builtins_check.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/builtins/CMakeFiles/builtins_check.dir/depend
