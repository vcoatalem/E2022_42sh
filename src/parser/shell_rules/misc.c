#include "../parser.h"

// optionnal_line_breaks -> '\n' optionnal_line_breaks
// optionnal_line_breaks -> epsilon
void sh_rule_optionnal_line_breaks(struct rule_array *rules)
{
    struct rule *rule = rule_build(RULE_LINE_BREAKS,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_LINE_BREAKS),
            NULL);
    struct rule *rule_eps = rule_build(RULE_LINE_BREAKS,
            symbol_epsilon(),
            NULL);
    rule_array_add(rules, rule);
    rule_array_add(rules, rule_eps);
}
