add_library(parser
    parse.c
    grammar.c
    rule.c
    shell_rules/rule_and_or.c
    shell_rules/rule_command.c
    shell_rules/rule_element.c
    shell_rules/rule_input.c
    shell_rules/rule_list.c
    shell_rules/rule_pipeline.c
    shell_rules/rule_redirection.c
    test.c
    test_runner.c)

target_link_libraries(parser lexer ast)


# BASIC PARSER TEST

add_executable(test_parser_basic tests/test_parser_basic.c)

target_link_libraries(test_parser_basic parser)

set_target_properties(test_parser_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

######################

# List all tests
add_custom_target(parser_check
    DEPENDS test_parser_basic
)
