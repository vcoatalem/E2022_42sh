#include "../parser.h"

// COMMAND -> ELEMENT ARG_LIST REDIRECTION_LIST
// COMMAND -> ARG_LIST REDIRECTION REDIRECTION_LIST
//TODO: add redirections
static void sh_rule_simple_command(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_SIMPLE_COMMAND,
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    struct rule *rule_b = rule_build(RULE_SIMPLE_COMMAND,
            symbol_create(0, RULE_REDIR),
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

static void sh_rule_shell_command(struct rule_array *rules)
{
    struct rule *rule_var_decl = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_VARDEC),
            NULL);
    struct rule *rule_if = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_IF),
            NULL);
    struct rule *rule_while = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_WHILE),
            NULL);
    struct rule *rule_until = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_UNTIL),
            NULL);
    struct rule *rule_brackets = rule_build(RULE_SHELL_COMMAND,
            symbol_create(TOKEN_LEFT_BRACKET, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(TOKEN_RIGHT_BRACKET, 0),
            NULL);
    struct rule *rule_parenthesis = rule_build(RULE_SHELL_COMMAND,
            symbol_create(TOKEN_LEFT_PARENTHESIS, 0),
            symbol_create(0, RULE_COMPOUND_LIST),
            symbol_create(TOKEN_RIGHT_PARENTHESIS, 0),
            NULL);
    struct rule *rule_funcdec = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_FUNCDEC),
            NULL);
    rule_array_add(rules, rule_var_decl);
    rule_array_add(rules, rule_if);
    rule_array_add(rules, rule_while);
    rule_array_add(rules, rule_until);
    rule_array_add(rules, rule_brackets);
    rule_array_add(rules, rule_parenthesis);
    rule_array_add(rules, rule_funcdec);
}

static void sh_rule_command(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_SIMPLE_COMMAND),
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_SHELL_COMMAND),
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

static void sh_rule_command_not(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_COMMAND_NOT,
            symbol_create(TOKEN_EXCLAMATION_POINT, 0),
            symbol_create(0, RULE_COMMAND),
            NULL));
}

void sh_rule_command_groups(struct rule_array *rules)
{
    sh_rule_command(rules);
    sh_rule_shell_command(rules);
    sh_rule_simple_command(rules);
    sh_rule_command_not(rules);
}
