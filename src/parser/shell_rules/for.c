#include "../parser.h"

static void sh_rule_for_element_list(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_FOR_ELEMENT_LIST,
            symbol_create(0, RULE_ELEMENT_ANY),
            symbol_create(0, RULE_FOR_ELEMENT_LIST),
            NULL));
    rule_array_add(rules, rule_build(RULE_FOR_ELEMENT_LIST,
            symbol_epsilon(),
            NULL));
}

static void sh_rule_for_linebreak(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_FOR_LINEBREAK,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_FOR_LINEBREAK),
            NULL));
    rule_array_add(rules, rule_build(RULE_FOR_LINEBREAK,
            symbol_epsilon(),
            NULL));
}

static void sh_rule_for_delim(struct rule_array *rules)
{ 
    rule_array_add(rules, rule_build(RULE_FOR_DELIM,
            symbol_create(TOKEN_SEMI_COLON, 0),
            NULL));
    rule_array_add(rules, rule_build(RULE_FOR_DELIM,
            symbol_create(TOKEN_EOL, 0),
            NULL));
}

static void sh_rule_for_clause(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_FOR_CLAUSE,
            symbol_create(TOKEN_SEMI_COLON, 0),
            NULL));
    rule_array_add(rules, rule_build(RULE_FOR_CLAUSE,
            symbol_create(0, RULE_FOR_LINEBREAK),
            symbol_create(TOKEN_IN, 0),
            symbol_create(0, RULE_FOR_ELEMENT_LIST),
            symbol_create(0, RULE_FOR_DELIM),
            NULL));
}

static void sh_rule_for(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_FOR,
            symbol_create(TOKEN_FOR, 0),
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_FOR_CLAUSE),
            symbol_create(0, RULE_FOR_LINEBREAK),
            symbol_create(0, RULE_DO_GROUP),
            NULL));
}


void sh_rule_for_groups(struct rule_array *rules)
{
    sh_rule_for(rules);
    sh_rule_for_clause(rules);
    sh_rule_for_element_list(rules);
    sh_rule_for_delim(rules);
    sh_rule_for_linebreak(rules);
}
