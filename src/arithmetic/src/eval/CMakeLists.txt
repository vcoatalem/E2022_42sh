add_library(arithmetic arithmetic_substitution.c)

target_link_libraries(arithmetic
        arithmetic_ast
        arithmetic_lexer
        arithmetic_parser
        arithmetic_utils
        hashtable)
