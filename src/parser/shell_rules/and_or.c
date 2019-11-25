#include "../parser.h"

static void sh_rule_or_linebreak(struct rule_array *rules)
{
    struct rule *rule_repeat = rule_build(RULE_OR_LINEBREAK,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_OR_LINEBREAK),
            NULL);
    struct rule *rule_pass = rule_build(RULE_OR_LINEBREAK,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule_repeat);
    rule_array_add(rules, rule_pass);
}

static void sh_rule_and_linebreak(struct rule_array *rules)
{
    struct rule *rule_repeat = rule_build(RULE_AND_LINEBREAK,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_AND_LINEBREAK),
            NULL);
    struct rule *rule_pass = rule_build(RULE_AND_LINEBREAK,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule_repeat);
    rule_array_add(rules, rule_pass);
}

static void sh_rule_or(struct rule_array *rules)
{ 
    struct rule *rule = rule_build(RULE_OR,
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_OR_CONCAT),
            NULL);
    rule_array_add(rules, rule);
}

static void sh_rule_or_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_OR_CONCAT,
            symbol_create(TOKEN_DOUBLE_PIPE, 0),
            symbol_create(0, RULE_OR_LINEBREAK),
            symbol_create(0, RULE_OR),
            NULL);
    struct rule *rule_eps = rule_build(RULE_OR_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

static void sh_rule_and_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_AND_CONCAT,
            symbol_create(TOKEN_DOUBLE_AMPERSAND, 0),
            symbol_create(0, RULE_AND_LINEBREAK),
            symbol_create(0, RULE_AND_OR),
            NULL);
    struct rule *rule_eps = rule_build(RULE_AND_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

static void sh_rule_and_or(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_AND_OR,
            symbol_create(0, RULE_PIPELINE),
            symbol_create(0, RULE_OR_CONCAT),
            symbol_create(0, RULE_AND_CONCAT),
            NULL);
    rule_array_add(rules, rule);
}

void sh_rule_and_or_groups(struct rule_array *rules)
{
    sh_rule_or(rules);
    sh_rule_and_or(rules);
    sh_rule_and_concat(rules);
    sh_rule_or_concat(rules);
    sh_rule_and_linebreak(rules);
    sh_rule_or_linebreak(rules);
}
