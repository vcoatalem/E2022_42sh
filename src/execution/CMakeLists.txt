add_library(execution
    command.c
    pipe.c
    redirection.c
    apply_redirections.c
    subshell.c)

target_link_libraries(execution builtins ast hashtable)
target_link_libraries(execution -lreadline)

### BASIC EXECUTION TEST

add_executable(test_execution_basic tests/basic/test_basic.c)

target_link_libraries(test_execution_basic execution)

set_target_properties(test_execution_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_execution_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/execution/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/execution/test_execution_basic" 0
)




### BUILTIN EXECUTION TEST

add_executable(test_execution_builtins tests/builtins/test_execution_builtins.c)

target_link_libraries(test_execution_builtins execution)

set_target_properties(test_execution_builtins
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_execution_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/execution/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/execution/test_execution_builtins" 1
)




### SUBSHELL TEST

add_executable(test_execution_subshell tests/subshell/test_subshell.c)

target_link_libraries(test_execution_subshell execution)

set_target_properties(test_execution_subshell
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

######################

# List all tests
add_custom_target(execution_check
    DEPENDS test_execution_basic
    DEPENDS test_execution_builtins
    DEPENDS test_execution_subshell
)
