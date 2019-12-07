#include "../parser.h"

//case rules:

// case: `case` -> case -> ELEMENT -> case_linebreaks -> `in`
//                                  -> case_linebreaks -> case_clause

// case_clause: -> case_item -> case_linebreaks-> compound_list case_concat
//              -> case_delim -> 'esac'

// case_concat: (;;|\n*) case_clause

// case_delim: (;;|\n*)


//case_linebreaks
static void sh_rule_case_linebreak(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_LINEBREAK,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_CASE_LINEBREAK),
            NULL));
    rule_array_add(rules, rule_build(RULE_CASE_LINEBREAK,
            symbol_epsilon(),
            NULL));
}

//case
static void sh_rule_case(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_CASE,
            symbol_create(TOKEN_CASE, 0),
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_CASE_LINEBREAK),
            symbol_create(TOKEN_IN, 0),
            symbol_create(0, RULE_CASE_LINEBREAK),
            symbol_create(0, RULE_CASE_CLAUSE),
            NULL);
    rule_array_add(rules, rule);
}

//case_delim
static void sh_rule_case_clause_delim(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_DELIM,
            symbol_create(TOKEN_DOUBLE_SEMICOLON, 0),
            NULL));
    rule_array_add(rules, rule_build(RULE_CASE_DELIM,
            symbol_create(TOKEN_EOL, 0),
            NULL));
}

//case_clause
static void sh_rule_case_clause(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_CLAUSE,
            symbol_create(0, RULE_CASE_ITEM),
            symbol_create(0, RULE_CASE_DELIM),
            symbol_create(0, RULE_CASE_CLAUSE_CONCAT),
            NULL));
}

//case_clause_concat
static void sh_rule_case_clause_concat(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_CLAUSE_CONCAT,
            symbol_create(0, RULE_CASE_CLAUSE),
            NULL));
    rule_array_add(rules, rule_build(RULE_CASE_CLAUSE_CONCAT,
            symbol_create(TOKEN_ESAC, 0),
            NULL));
}

//case_clause_item
static void sh_rule_case_item_concat(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_ITEM_CONCAT,
            symbol_create(TOKEN_PIPE, 0),
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_CASE_ITEM_CONCAT),
            NULL));
    rule_array_add(rules, rule_build(RULE_CASE_ITEM_CONCAT,
            symbol_epsilon(),
            NULL));
}

//case_utem
static void sh_rule_case_item(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_CASE_ITEM,
            symbol_create(TOKEN_LEFT_PARENTHESIS, 0),
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_CASE_ITEM_CONCAT),
            symbol_create(TOKEN_RIGHT_PARENTHESIS, 0),
            symbol_create(0, RULE_CASE_LINEBREAK),
            symbol_create(0, RULE_COMPOUND_LIST),
            NULL));
    rule_array_add(rules, rule_build(RULE_CASE_ITEM,
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_CASE_ITEM_CONCAT),
            symbol_create(TOKEN_RIGHT_PARENTHESIS, 0),
            symbol_create(0, RULE_CASE_LINEBREAK),
            symbol_create(0, RULE_COMPOUND_LIST),
            NULL));
}

void sh_rule_case_groups(struct rule_array *rules)
{
    sh_rule_case_linebreak(rules);
    sh_rule_case(rules);
    sh_rule_case_clause_concat(rules);
    sh_rule_case_clause(rules);
    sh_rule_case_clause_delim(rules);
    sh_rule_case_item(rules);
    sh_rule_case_item_concat(rules);
    //sh_rule_end(rules);
}
