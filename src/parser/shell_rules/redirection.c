#include "../parser.h"

static void sh_rule_redirection_symbol_primary(struct rule_array *rules)
{
    struct rule *rule_less = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_LESS, 0),
            NULL);
    struct rule *rule_great = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_GREAT, 0),
            NULL);
    rule_array_add(rules, rule_less);
    rule_array_add(rules, rule_great);
}

/*static */void sh_rule_redirection_symbol_basic(struct rule_array *rules)
{
    struct rule *rule_double_less = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_DOUBLE_LESS, 0),
            NULL);
    struct rule *rule_double_great = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_DOUBLE_GREAT, 0),
            NULL);
    struct rule *rule_less_ampersand = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_LESS_AMPERSAND, 0),
            NULL);
    struct rule *rule_great_ampersand = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_GREAT_AMPERSAND, 0),
            NULL);
    rule_array_add(rules, rule_double_less);
    rule_array_add(rules, rule_double_great);
    rule_array_add(rules, rule_less_ampersand);
    rule_array_add(rules, rule_great_ampersand);
}

/*static */void sh_rule_redirection_symbol_advanced(struct rule_array *rules)
{
    struct rule *rule_double_less_dash = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_DOUBLE_LESS_DASH, 0),
            NULL);
    struct rule *rule_great_pipe = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_GREAT_PIPE, 0),
            NULL);
    struct rule *rule_less_great = rule_build(RULE_REDIRECTION_SYMBOL,
            symbol_create(TOKEN_LESS_GREAT, 0),
            NULL);
    rule_array_add(rules, rule_double_less_dash);
    rule_array_add(rules, rule_great_pipe);
    rule_array_add(rules, rule_less_great);
}

/* REDIRECTION_SYMBOL -> `>`
** REDIRECTION_SYMBOL -> `<`
** ...
*/
void sh_rule_redirection_symbol(struct rule_array *rules)
{
    sh_rule_redirection_symbol_primary(rules);
    //sh_rule_redirection_symbol_basic(rules);
    //sh_rule_redirection_symbol_advanced(rules);
}

/* IONUMBER -> `0`
** IONUMBER -> `1`
** IONUMBER -> `2`
*/
void sh_rule_ionumber(struct rule_array *rules)
{
    struct rule *rule_stdin = rule_build(RULE_IONUMBER,
            symbol_create(TOKEN_STDIN, 0),
            NULL);
    struct rule *rule_stdout = rule_build(RULE_IONUMBER,
            symbol_create(TOKEN_STDOUT, 0),
            NULL);
    struct rule *rule_stderr = rule_build(RULE_IONUMBER,
            symbol_create(TOKEN_STDERR, 0),
            NULL);
    rule_array_add(rules, rule_stdin);
    rule_array_add(rules, rule_stdout);
    rule_array_add(rules, rule_stderr);
}


/* REDIRECTION -> IONUMBER REDIRECTION_SYMBOL ELEMENT
** REDIRECTION -> REDIRECTION_SYMBOL
** REDIRECTION -> REDIRECTION_SYMBOL ELEMENT
*/
void sh_rule_redirection(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_REDIRECTION,
            symbol_create(0, RULE_IONUMBER),
            symbol_create(0, RULE_REDIRECTION_SYMBOL),
            symbol_create(0, RULE_ELEMENT),
            NULL);
    struct rule *rule_b = rule_build(RULE_REDIRECTION,
            symbol_create(0, RULE_REDIRECTION_SYMBOL),
            NULL);
    struct rule *rule_c = rule_build(RULE_REDIRECTION,
            symbol_create(0, RULE_REDIRECTION_SYMBOL),
            symbol_create(0, RULE_ELEMENT),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
    rule_array_add(rules, rule_c);
}

/* REDIRECTION_LIST -> REDIRECTION REDIRECTION_LIST
** REDIRECTION_LIST -> epsilon
*/
void sh_rule_redirection_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_REDIRECTION_LIST,
            symbol_create(0, RULE_REDIRECTION),
            symbol_create(0, RULE_REDIRECTION_LIST),
            NULL);
    struct rule *rule_epsilon = rule_build(RULE_REDIRECTION_LIST,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_epsilon);
}
