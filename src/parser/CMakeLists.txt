add_library(parser
    # rule.c
    # rule_array.c
    # symbol.c
    # symbol_array.c
    # stamp.c
    # operations.c
    # table.c
    # stack.c
    # parse.c
    # shell_rules/element.c
    # shell_rules/command.c
    # shell_rules/redirection.c
    # shell_rules/misc.c
    # shell_rules/pipeline.c
    # shell_rules/and_or.c
    # shell_rules/input.c
    # ast_build/node_string.c
    # ast_build/node_operator.c
    tmp_parse.c
)
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

add_executable(test_grammar_basic tests/test_grammar_basic.c)

target_link_libraries(test_grammar_basic parser)

set_target_properties(test_grammar_basic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)
# BASIC GRAMMAR TEST

add_custom_target(parser_check
    DEPENDS test_parser_basic
    DEPENDS test_grammar_basic
)
