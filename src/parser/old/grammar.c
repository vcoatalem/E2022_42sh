#include "parser.h"

struct grammar *grammar_build(void)
{
    struct grammar *g = calloc(1, sizeof(struct grammar));
    g->n_rules = NB_RULES;
    g->rules = calloc(sizeof(void*), NB_RULES + 1);
    g->rules[RULE_INPUT] = rule_input();
    g->rules[RULE_LIST] = rule_list();
    g->rules[RULE_AND_OR] = rule_and_or();
    g->rules[RULE_AND] = rule_and();
    g->rules[RULE_OR] = rule_or();
    g->rules[RULE_PIPELINE] = rule_pipeline();
    g->rules[RULE_COMMAND] = rule_command();
    g->rules[RULE_SIMPLE_COMMAND] = rule_simple_command();
    g->rules[RULE_IONUMBER] = rule_ionumber();
    g->rules[RULE_REDIRECTION_SYMBOL] = rule_redirection_symbol();
    g->rules[RULE_REDIRECTION] = rule_redirection();
    g->rules[RULE_REDIRECTION_LIST] = rule_redirection_list();
    g->rules[RULE_ELEMENT] = rule_element();
    g->rules[RULE_ARG_LIST] = rule_arg_list();
    return g;
}

void grammar_free(struct grammar *grammar)
{
    for (size_t i = 1; i < NB_RULES; i++)
    {
        rule_free(grammar->rules[i]);
    }
    free(grammar->rules);
    free(grammar);
}
