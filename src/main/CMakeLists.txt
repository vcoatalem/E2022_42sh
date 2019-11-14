add_executable(42sh main.c)

target_link_libraries(42sh PRIVATE options lexer parser ast execution)
target_link_libraries(42sh PUBLIC -lreadline)
