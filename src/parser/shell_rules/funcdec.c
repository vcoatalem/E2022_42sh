#include "../parser.h"

static void sh_rule_funcdec_body(struct rule_array *rules)
{
    struct rule *rule_eol = rule_build(RULE_FUNCDEC_BODY,
            symbol_create(TOKEN_EOL, 0),
            symbol_create(0, RULE_FUNCDEC_BODY),
            NULL);
    struct rule *rule = rule_build(RULE_FUNCDEC_BODY,
            symbol_create(0, RULE_SHELL_COMMAND),
            NULL);
    rule_array_add(rules, rule_eol);
    rule_array_add(rules, rule);
}

static void sh_rule_funcdec(struct rule_array *rules)
{
    rule_array_add(rules, rule_build(RULE_FUNCDEC,
            symbol_create(TOKEN_FUNCTION, 0),
            symbol_create(TOKEN_FUNCDEC, 0),
            symbol_create(0, RULE_FUNCDEC_BODY),
            NULL));
    rule_array_add(rules, rule_build(RULE_FUNCDEC,
            symbol_create(TOKEN_FUNCDEC, 0),
            symbol_create(0, RULE_FUNCDEC_BODY),
            NULL));
}

void sh_rule_funcdec_groups(struct rule_array *rules)
{
    sh_rule_funcdec(rules);
    sh_rule_funcdec_body(rules);
}
