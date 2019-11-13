add_library(parser test.c test_runner.c)

target_link_libraries(parser lexer)
