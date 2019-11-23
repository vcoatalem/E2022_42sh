#include "../parser.h"

static void sh_rule_var_assignment(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_VARDEC,
            symbol_create(TOKEN_ASSIGNMENT, 0),
            NULL);
    rule_array_add(rules, rule);
}

void sh_rule_misc(struct rule_array *rules)
{
    sh_rule_var_assignment(rules);
}
