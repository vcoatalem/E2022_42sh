add_library(arithmetic_parser parser.c)

target_link_libraries(arithmetic_parser
        arithmetic_lexer
        arithmetic_ast)
