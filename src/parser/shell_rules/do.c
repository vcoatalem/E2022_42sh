#include "../parser.h"

static void sh_rule_do_group(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_DO_GROUP,
            symbol_create(TOKEN_DO, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(TOKEN_DONE, 0),
            NULL);
    rule_array_add(rules, rule);
}

static void sh_rule_while(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_WHILE,
            symbol_create(TOKEN_WHILE, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(0, RULE_DO_GROUP),
            NULL);
    rule_array_add(rules, rule);
}

static void sh_rule_until(struct rule_array *rules)
{
   struct rule *rule = rule_build(RULE_UNTIL,
            symbol_create(TOKEN_UNTIL, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(0, RULE_DO_GROUP),
            NULL);
    rule_array_add(rules, rule);
}

void sh_rule_do_groups(struct rule_array *rules)
{
    sh_rule_do_group(rules);
    sh_rule_while(rules);
    sh_rule_until(rules);
}
