#include "../parser.h"

// ELEMENT -> `word`
void sh_rule_element(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ELEMENT,
            symbol_create(TOKEN_WORD, 0),
            NULL);
    rule_array_add(rules, rule);
}

// ELEMENT_LIST -> ELEMENT ELEMENT_LIST
// ELEMENT_LIST -> eps
void sh_rule_element_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ELEMENT_LIST,
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_ELEMENT_LIST),
            NULL);
    struct rule *rule_eps = rule_build(RULE_ELEMENT_LIST,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

// ARG_LIST -> ELEMENT ELEMENT_LIST
void sh_rule_arg_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ARG_LIST,
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_ELEMENT_LIST),
            NULL);
    rule_array_add(rules, rule);
}
