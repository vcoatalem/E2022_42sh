add_library(arithmetic_substitution arithmetic_substitution.c)

target_link_libraries(arithmetic_substitution
        arithmetic_ast
        arithmetic_lexer
        arithmetic_parser
        arithmetic_utils
        hashtable)
