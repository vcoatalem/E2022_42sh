#include "../parser.h"

// ELEMENT_EXPAND -> expand word
static void sh_rule_element_expand(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_EXPAND,
            symbol_create(TOKEN_WORD_EXPAND, 0), NULL));
}

// ELEMENT_SUBSHELL -> subshell word
static void sh_rule_element_subshell(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_SUBSHELL,
            symbol_create(TOKEN_SUBSHELL, 0), NULL));
}

// ELEMENT ARITHMETIC -> arithmetic word
static void sh_rule_element_arithmetic(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_ARITHMETIC,
            symbol_create(TOKEN_ARITHMETIC, 0), NULL));
}

// ELEMENT ARITHMETIC -> arithmetic word
static void sh_rule_element_tilde(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_TILDE,
            symbol_create(TOKEN_WORD_TILDE, 0), NULL));
}

// ELEMENT NO SUBSTITUTE -> single_quoted word
static void sh_rule_element_no_substitution(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_NO_SUBSTITUTION,
            symbol_create(TOKEN_WORD_NO_SUBSTITUTION, 0), NULL));
}

// ELEMENT -> `word`
static void sh_rule_element(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(TOKEN_WORD, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(0, RULE_ELEMENT_EXPAND), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(0, RULE_ELEMENT_SUBSHELL), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(0, RULE_ELEMENT_ARITHMETIC), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(0, RULE_ELEMENT_NO_SUBSTITUTION), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT,
            symbol_create(0, RULE_ELEMENT_TILDE), NULL));
}

// ELEMENT_LIST -> ELEMENT ELEMENT_LIST
// ELEMENT_LIST -> epsilon
static void sh_rule_element_list(struct rule_array *rules)
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
static void sh_rule_arg_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ARG_LIST,
            symbol_create(0, RULE_ELEMENT),
            symbol_create(0, RULE_ELEMENT_ANY_LIST),
            NULL);
    rule_array_add(rules, rule);
}

//represents any word that can be considered an arg, including reserved words
//such as 'for', 'else', etc..
static void sh_rule_element_any(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_WORD, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(0, RULE_ELEMENT_SUBSHELL), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(0, RULE_ELEMENT_ARITHMETIC), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(0, RULE_ELEMENT_EXPAND), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(0, RULE_ELEMENT_NO_SUBSTITUTION), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(0, RULE_ELEMENT_TILDE), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_WORD, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_IF, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_ELSE, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_ELIF, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_FI, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_DO, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_DONE, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_FOR, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_CASE, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_ESAC, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_EXCLAMATION_POINT, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_WHILE, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_UNTIL, 0), NULL));
    rule_array_add(rules, rule_build(RULE_ELEMENT_ANY,
            symbol_create(TOKEN_ASSIGNMENT, 0), NULL));

}

static void sh_rule_element_any_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_ELEMENT_ANY_LIST,
            symbol_create(0, RULE_ELEMENT_ANY),
            symbol_create(0, RULE_ELEMENT_ANY_LIST),
            NULL);
    struct rule *rule_eps = rule_build(RULE_ELEMENT_ANY_LIST,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

void sh_rule_element_groups(struct rule_array *rules)
{
    sh_rule_element(rules);
    sh_rule_element_no_substitution(rules);
    sh_rule_element_expand(rules);
    sh_rule_element_subshell(rules);
    sh_rule_element_arithmetic(rules);
    sh_rule_element_tilde(rules);
    sh_rule_element_list(rules);
    sh_rule_arg_list(rules);
    sh_rule_element_any(rules);
    sh_rule_element_any_list(rules);
}
