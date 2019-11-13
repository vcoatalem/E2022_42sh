cmake_minimum_required(VERSION 3.0)

project(42sh LANGUAGES C)
add_compile_options(-Wall -Wextra -pedantic -Werror -std=c99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/src/)


#launch all unit tests
add_custom_target(check
    DEPENDS execution_check
    DEPENDS ast_check
    DEPENDS lexer_check
)
