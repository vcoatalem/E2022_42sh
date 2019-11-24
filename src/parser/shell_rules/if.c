#include "../parser.h"

static void sh_rule_then(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_THEN,
            symbol_create(TOKEN_THEN, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            NULL);
    rule_array_add(rules, rule);
}

// IF -> `if` LIST `then` LIST ELSE_CONCAT `fi`
static void sh_rule_if(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_IF,
            symbol_create(TOKEN_IF, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(0, RULE_THEN),
            symbol_create(0, RULE_ELSE_CONCAT),
            symbol_create(TOKEN_FI, 0),
            NULL);
    rule_array_add(rules, rule);
}

// ELSE_CLAUSE -> `else` LIST
// ELSE_CLAUSE -> `elif` LIST `then` LIST ELSE_CLAUSE
// ELSE_CLAUSE -> epsilon
static void sh_rule_else_concat(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ELSE_CONCAT,
            symbol_create(TOKEN_ELSE, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            NULL);
    struct rule *rule_elif = rule_build(RULE_ELSE_CONCAT,
            symbol_create(TOKEN_ELIF, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(TOKEN_THEN, 0),
            symbol_create(0, RULE_COMPOUND_LIST_BREAK),
            symbol_create(0, RULE_ELSE_CONCAT),
            NULL);
    struct rule *rule_eps = rule_build(RULE_ELSE_CONCAT,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_elif);
    rule_array_add(rules, rule_eps);
}

void sh_rule_if_groups(struct rule_array *rules)
{
    sh_rule_if(rules);
    sh_rule_then(rules);
    sh_rule_else_concat(rules);
}
