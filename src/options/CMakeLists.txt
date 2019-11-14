add_library(options options.c)

# BASIC OPTIONS TEST

add_executable(test_options tests/test_options.c)

target_link_libraries(test_options options)

set_target_properties(test_options
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_options
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/options/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/options/test_options"
)

######################

# List all tests
add_custom_target(options_check
    DEPENDS test_options
)
