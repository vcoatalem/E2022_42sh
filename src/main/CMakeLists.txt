add_executable(42sh
    main.c
    readline.c
    execute.c
    history.c
    ressources.c
    advanced_prompt.c)

target_link_libraries(42sh PRIVATE options lexer parser ast execution hashtable builtins)
target_link_libraries(42sh PUBLIC -lreadline)
