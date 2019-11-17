#include "../parser.h"

//pipe -> '|' optionnal_line_breaks command
void sh_rule_pipe(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_PIPE,
            symbol_create(TOKEN_PIPE, 0),
            symbol_create(0, RULE_OPTIONNAL_LINE_BREAKS),
            NULL);
    rule_array_add(rules, rule);
}

//pipeline -> command pipe
//pipeline -> '!' command pipe
//pipeline -> epsilon
void sh_rule_pipeline(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_PIPELINE,
            symbol_create(0, RULE_COMMAND),
            symbol_create(0, RULE_PIPELINE),
            NULL);
    struct rule *rule_excl = rule_build(RULE_PIPELINE,
            symbol_create(TOKEN_EXCLAMATION_POINT, 0),
            symbol_create(0, RULE_COMMAND),
            symbol_create(0, RULE_PIPELINE),
            NULL);
    struct rule *rule_eps = rule_build(RULE_PIPELINE,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_excl);
    rule_array_add(rules, rule_eps);
}
