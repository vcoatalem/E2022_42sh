#include "../parser.h"

void sh_rule_and_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_AND_CONCAT,
            symbol_create(TOKEN_DOUBLE_AMPERSAND, 0),
            //symbol_create(0, RULE_OPTIONNAL_LINE_BREAKS),
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_AND_CONCAT),
            NULL);
    struct rule *rule_eps = rule_build(RULE_AND_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

void sh_rule_and(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_AND,
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_AND_CONCAT),
            NULL);
    rule_array_add(rules, rule);
}


void sh_rule_or_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_OR_CONCAT,
            symbol_create(TOKEN_DOUBLE_PIPE, 0),
            //symbol_create(0, RULE_OPTIONNAL_LINE_BREAKS),
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_OR_CONCAT),
            NULL);
    struct rule *rule_eps = rule_build(RULE_OR_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

void sh_rule_or(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_OR,
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_OR_CONCAT),
            NULL);
    rule_array_add(rules, rule);
}

void sh_rule_and_or(struct rule_array *rules)
{
    struct rule *rule_and = rule_build(RULE_AND_OR,
            symbol_create(0, RULE_AND),
            NULL);
    struct rule *rule_or = rule_build(RULE_AND_OR,
            symbol_create(0, RULE_OR),
            NULL);
    rule_array_add(rules, rule_and);
    rule_array_add(rules, rule_or);
}
