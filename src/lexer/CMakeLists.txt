add_library(lexer   token/token.c token/token_string.c token_to_handler.c token_array.c handlers.c)

# BASIC EXECUTION TEST

add_executable(test_lexer_basic tests/test_basic.c)

target_link_libraries(test_lexer_basic lexer)

set_target_properties(test_lexer_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_lexer_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/lexer/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/lexer/test_lexer_basic"
)

######################

# List all tests
add_custom_target(lexer_check
    DEPENDS test_lexer_basic
)
