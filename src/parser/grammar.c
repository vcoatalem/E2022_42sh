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
    g->rules[RULE_REDIRECTION] = rule_redirection();
    g->rules[RULE_ELEMENT] = rule_element();
    return g;
}
