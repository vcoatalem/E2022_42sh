#include "../parser.h"

// COMMAND -> ELEMENT ARG_LIST REDIRECTION_LIST
// COMMAND -> ARG_LIST REDIRECTION REDIRECTION_LIST
//TODO: add redirections
void sh_rule_command(struct rule_array *rules)
{
#if 0
    struct rule *rule_a = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIRECTION_LIST),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIRECTION),
            symbol_create(0, RULE_REDIRECTION_LIST),
            NULL);
#endif
    struct rule *rule_a = rule_build(RULE_COMMAND,
            symbol_create(0, RULE_ARG_LIST),
            symbol_create(0, RULE_REDIRECTION_LIST),
            NULL);
    rule_array_add(rules, rule_a);
    //rule_array_add(rules, rule_b);
}
