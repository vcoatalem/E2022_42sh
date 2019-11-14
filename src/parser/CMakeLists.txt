add_library(parser parse.c grammar.c rule.c test.c test_runner.c)

target_link_libraries(parser lexer ast)
