#include "../parser.h"

// COMMAND -> ELEMENT ARG_LIST REDIRECTION_LIST
// COMMAND -> ARG_LIST REDIRECTION REDIRECTION_LIST
//TODO: add redirections
void sh_rule_command(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    rule_array_add(rules, rule_a);
    //rule_array_add(rules, rule_b);
}
