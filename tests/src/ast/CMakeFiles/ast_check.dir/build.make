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

# Utility rule file for ast_check.

# Include the progress variables for this target.
include src/ast/CMakeFiles/ast_check.dir/progress.make

src/ast/CMakeFiles/ast_check: src/ast/test_ast_basic
src/ast/CMakeFiles/ast_check: src/ast/test_ast_print
src/ast/CMakeFiles/ast_check: src/ast/test_ast_exec


ast_check: src/ast/CMakeFiles/ast_check
ast_check: src/ast/CMakeFiles/ast_check.dir/build.make

.PHONY : ast_check

# Rule to build all files generated by this target.
src/ast/CMakeFiles/ast_check.dir/build: ast_check

.PHONY : src/ast/CMakeFiles/ast_check.dir/build

src/ast/CMakeFiles/ast_check.dir/clean:
	cd /home/xarang/E2022_42sh/tests/src/ast && $(CMAKE_COMMAND) -P CMakeFiles/ast_check.dir/cmake_clean.cmake
.PHONY : src/ast/CMakeFiles/ast_check.dir/clean

src/ast/CMakeFiles/ast_check.dir/depend:
	cd /home/xarang/E2022_42sh/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xarang/E2022_42sh /home/xarang/E2022_42sh/src/ast /home/xarang/E2022_42sh/tests /home/xarang/E2022_42sh/tests/src/ast /home/xarang/E2022_42sh/tests/src/ast/CMakeFiles/ast_check.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ast/CMakeFiles/ast_check.dir/depend
