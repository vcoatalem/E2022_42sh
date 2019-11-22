#include "../parser.h"

static void sh_rule_compound_list_delim(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMPOUND_LIST_DELIM,
            symbol_create(TOKEN_SEMI_COLON, 0),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMPOUND_LIST_DELIM,
            symbol_create(TOKEN_AMPERSAND, 0),
            NULL);
    struct rule *rule_c = rule_build(RULE_COMPOUND_LIST_DELIM,
            symbol_create(TOKEN_EOL, 0),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
    rule_array_add(rules, rule_c);
}

static void sh_rule_compound_list_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_COMPOUND_LIST_CONCAT,
            symbol_create(0, RULE_COMPOUND_LIST_DELIM),
            symbol_create(0, RULE_COMPOUND_LIST),
            NULL);
    struct rule *rule_eps = rule_build(RULE_COMPOUND_LIST_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

static void sh_rule_compound_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_COMPOUND_LIST,
            symbol_create(0, RULE_AND_OR),
            symbol_create(0, RULE_COMPOUND_LIST_CONCAT),
            NULL);
    struct rule *rule_repeat = rule_build(RULE_COMPOUND_LIST,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_COMPOUND_LIST),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_repeat);
}

void sh_rule_compound_list_groups(struct rule_array *rules)
{
    sh_rule_compound_list(rules);
    sh_rule_compound_list_concat(rules);
    sh_rule_compound_list_delim(rules);
}
