#include "../parser.h"

// COMMAND -> ELEMENT ARG_LIST REDIRECTION_LIST
// COMMAND -> ARG_LIST REDIRECTION REDIRECTION_LIST
//TODO: add redirections
void sh_rule_simple_command(struct rule_array *rules)
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

void sh_rule_shell_command(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_SHELL_COMMAND,
            symbol_create(0, RULE_IF),
            NULL);
    rule_array_add(rules, rule);
}

void sh_rule_command(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_SIMPLE_COMMAND),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_SHELL_COMMAND),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}
