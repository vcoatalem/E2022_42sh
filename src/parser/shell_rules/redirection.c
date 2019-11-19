#include "../parser.h"

static void sh_rule_redir_symbol_basic(struct rule_array *rules)
{
    struct rule *rule_less = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_LESS, 0),
            NULL);
    struct rule *rule_great = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_GREAT, 0),
            NULL);
    rule_array_add(rules, rule_less);
    rule_array_add(rules, rule_great);
}

//TODO: add this
void sh_rule_redir_symbol_more(struct rule_array *rules)
{
    struct rule *rule_double_less = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_DOUBLE_LESS, 0),
            NULL);
    struct rule *rule_double_less_dash = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_DOUBLE_LESS_DASH, 0),
            NULL);
    rule_array_add(rules, rule_double_less);
    rule_array_add(rules, rule_double_less_dash);
}

//TODO: add this
void sh_rule_redir_symbol_advanced(struct rule_array *rules)
{
    struct rule *rule_great_pipe = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_GREAT_PIPE, 0),
            NULL);
    struct rule *rule_less_great = rule_build(RULE_REDIR_SYMBOL,
            symbol_create(TOKEN_LESS_GREAT, 0),
            NULL);
    rule_array_add(rules, rule_great_pipe);
    rule_array_add(rules, rule_less_great);
}

void sh_rule_redir_symbol(struct rule_array *rules)
{
    sh_rule_redir_symbol_basic(rules);
}

void sh_rule_redir_to(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_REDIR_TO,
            symbol_create(0, RULE_IONUMBER),
            NULL);
    struct rule *rule_b = rule_build(RULE_REDIR_TO,
            symbol_create(TOKEN_WORD, 0),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

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

void sh_rule_redir(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_REDIR,
            symbol_create(0, RULE_IONUMBER),
            symbol_create(0, RULE_REDIR_SYMBOL),
            symbol_create(0, RULE_REDIR_TO),
            NULL);
    struct rule *rule_b = rule_build(RULE_REDIR,
            symbol_create(0, RULE_REDIR_SYMBOL),
            symbol_create(0, RULE_REDIR_TO),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

void sh_rule_redir_list(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_REDIR_LIST,
            symbol_create(0, RULE_REDIR),
            NULL);
    struct rule *rule_pass = rule_build(RULE_REDIR_LIST,
            symbol_epsilon(),
            NULL);
    struct rule *rule_repeat = rule_build(RULE_REDIR_LIST,
            symbol_create(0, RULE_REDIR_LIST),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_pass);
    rule_array_add(rules, rule_repeat);
}
