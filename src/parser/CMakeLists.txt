add_library(parser
    rule.c
    rule_array.c
    symbol.c
    symbol_array.c
    stamp.c
    operations.c
    table.c
    stack.c
    parse.c
    utils.c
    shell_rules/element.c
    shell_rules/command.c
    shell_rules/redirection.c
    shell_rules/if.c
    shell_rules/pipeline.c
    shell_rules/and_or.c
    shell_rules/list.c
    shell_rules/compound_list.c
    shell_rules/compound_list_break.c
    shell_rules/funcdec.c
    shell_rules/do.c
    shell_rules/for.c
    shell_rules/input.c
    shell_rules/misc.c
    shell_rules/case.c
    ast_build/node_string.c
    ast_build/node_operator.c
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

# fetch .sh script for output comparison
add_custom_command(TARGET test_parser_basic
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/parser/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/parser/test_parser_basic" "ast_basic"
)

######################

# MORE ADVANCED PARSER TEST

add_executable(test_parser_more tests/test_parser_more.c)

target_link_libraries(test_parser_more parser)

set_target_properties(test_parser_more
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

# fetch .sh script for output comparison
add_custom_command(TARGET test_parser_more
POST_BUILD
    COMMAND /bin/sh "${CMAKE_SOURCE_DIR}/src/parser/run_tests.sh" "${CMAKE_SOURCE_DIR}/build/src/parser/test_parser_more" "ast_more"
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
    DEPENDS test_grammar_basic
    DEPENDS test_parser_basic
    DEPENDS test_parser_more
)
