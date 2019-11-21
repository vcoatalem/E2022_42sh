#include "../parser.h"

//input -> list '\n'
//input -> list EOF
//input -> '\n'
//input -> 'EOF'

//for now replace list by and_or
//TODO: add command list
void sh_rule_input(struct rule_array *rules)
{
    struct rule *rule_a = rule_build(RULE_INPUT,
            symbol_create(0, RULE_LIST),
            symbol_create(TOKEN_EOF, 0),
            NULL);
    struct rule *rule_b = rule_build(RULE_INPUT,
            symbol_create(TOKEN_EOL, 0),
            NULL);
    rule_array_add(rules, rule_a);
    rule_array_add(rules, rule_b);
}
