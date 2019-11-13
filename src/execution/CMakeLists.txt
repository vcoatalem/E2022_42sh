add_library(execution command.c pipe.c redirection.c)

# BASIC EXECUTION TEST

add_executable(test_execution_basic tests/basic/test_basic.c)

target_link_libraries(test_execution_basic execution)

set_target_properties(test_execution_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_execution_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/execution/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/execution/test_execution_basic"
)

######################

# List all tests
add_custom_target(execution_check
    DEPENDS test_execution_basic
)
