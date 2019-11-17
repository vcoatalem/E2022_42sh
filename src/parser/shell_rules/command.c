#include "../parser.h"

// COMMAND -> ARG_LIST REDIRECTION_LIST
//TODO: add redirections
void sh_rule_command(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIRECTION_LIST),
            NULL);
    rule_array_add(rules, rule);
}
