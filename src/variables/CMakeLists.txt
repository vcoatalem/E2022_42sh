add_library(variables variables.c)
target_link_libraries(variables ast hashtable)

# BASIC PARSER TEST

add_executable(test_variables_basic tests/test_variables_basic.c)

target_link_libraries(test_variables_basic variables ast hashtable)

set_target_properties(test_variables_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_variables_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/variables/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/variables/test_variables_basic"
)

add_custom_target(variables_check
    DEPENDS test_variables_basic
)
