add_library(ast ast.c ast_print.c)

# BASIC INIT TEST

add_executable(test_ast_basic tests/ast.test.c)

target_link_libraries(test_ast_basic ast)

set_target_properties(test_ast_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
)

################

# DOT PRINT TEST

add_executable(test_ast_print tests/ast_print.test.c)

target_link_libraries(test_ast_print ast)

set_target_properties(test_ast_print
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
)

###############


# List all tests
add_custom_target(ast_check
    DEPENDS test_ast_basic
    DEPENDS test_ast_print
)
