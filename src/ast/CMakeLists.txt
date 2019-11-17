add_library(ast
    ast.c
    ast_print.c
    ast_execute.c
    handlers/and_or.c
    handlers/pipe.c
    handlers/if_then.c
    handlers/for.c
    handlers/until.c
    handlers/while.c)

target_link_libraries(ast execution)

# BASIC INIT TEST

add_executable(test_ast_basic tests/ast.test.c)

target_link_libraries(test_ast_basic ast)

set_target_properties(test_ast_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

################

# DOT PRINT TEST

add_executable(test_ast_print tests/ast_print.test.c)

target_link_libraries(test_ast_print ast)

set_target_properties(test_ast_print
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

###############

# EXEC PRINT TEST

add_executable(test_ast_exec tests/ast_execution.test.c)

target_link_libraries(test_ast_exec ast)

set_target_properties(test_ast_exec
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

###############


# List all tests
add_custom_target(ast_check
    DEPENDS test_ast_basic
    DEPENDS test_ast_print
    DEPENDS test_ast_exec
)
