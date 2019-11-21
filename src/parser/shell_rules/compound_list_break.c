#include "../parser.h"

void sh_rule_compound_list_break_line(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMPOUND_LIST_BREAK_LINE,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_LINE),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMPOUND_LIST_BREAK_LINE,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

void sh_rule_compound_list_break_delim(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_COMPOUND_LIST_BREAK_DELIM,
            symbol_create(TOKEN_SEMI_COLON, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_LINE),
            NULL);
    struct rule *rule_b = rule_build(RULE_COMPOUND_LIST_BREAK_DELIM,
            symbol_create(TOKEN_AMPERSAND, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_LINE),
            NULL);
    struct rule *rule_c = rule_build(RULE_COMPOUND_LIST_BREAK_DELIM,
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_LINE),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
    rule_array_add(rules, rule_c);
}

void sh_rule_compound_list_break_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_COMPOUND_LIST_BREAK_CONCAT,
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            NULL);
    struct rule *rule_eps = rule_build(RULE_COMPOUND_LIST_BREAK_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

void sh_rule_compound_list_break(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_COMPOUND_LIST_BREAK,
            symbol_create(0, RULE_AND_OR),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_DELIM),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK_CONCAT),
            NULL);
    struct rule *rule_repeat = rule_build(RULE_COMPOUND_LIST_BREAK,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_repeat);
}
