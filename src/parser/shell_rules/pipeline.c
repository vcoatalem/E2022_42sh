#include "../parser.h"

//pipe -> '|' pipeline
//pipe -> epsilon
static void sh_rule_pipe(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_PIPE,
            symbol_create(TOKEN_PIPE, 0),
            symbol_create(0, RULE_PIPELINE),
            NULL);
    struct rule *rule_eps = rule_build(RULE_PIPE,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}

//pipeline -> command pipe
//pipeline -> '!' command pipe
static void sh_rule_pipeline(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_PIPELINE,
            symbol_create(0, RULE_COMMAND),
            symbol_create(0, RULE_PIPE),
            NULL);
    struct rule *rule_b = rule_build(RULE_PIPELINE,
            symbol_create(TOKEN_EXCLAMATION_POINT, 0),
            symbol_create(0, RULE_COMMAND),
            symbol_create(0, RULE_PIPE),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}

void sh_rule_pipe_groups(struct rule_array *rules)
{
    sh_rule_pipe(rules);
    sh_rule_pipeline(rules);
}
