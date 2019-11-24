cmake_minimum_required(VERSION 3.0)

project(42sh LANGUAGES C)
add_compile_options(-g -Wall -Wextra -pedantic -Werror -std=c99 -D_DEFAULT_SOURCE -Isrc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/src/)

#launch test suite
add_custom_target(tests
    DEPENDS 42sh
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test_suite.sh ${CMAKE_SOURCE_DIR}/build/42sh
)

set_target_properties(tests
    PROPERTIES
    EXCLUDE_FROM_ALL "true"
)

#launch all unit tests
add_custom_target(check
    DEPENDS execution_check
    DEPENDS options_check
    DEPENDS parser_check
    # DEPENDS ast_check
    DEPENDS lexer_check
)

set_target_properties(check
    PROPERTIES
    EXCLUDE_FROM_ALL "true"
)
