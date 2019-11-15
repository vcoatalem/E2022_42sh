#include "../parser.h"

struct rule *rule_arg_list(void)
{
    struct rule *r = rule_init();
    struct test *t = test_rule_create(0, 1, RULE_ELEMENT);
    rule_add_test(r, t);
    return r;
}

struct rule *rule_redirection_list(void)
{
    struct rule *r = rule_init();
    struct test *t = test_rule_create(0, 1, RULE_REDIRECTION);
    rule_add_test(r, t);
    return r;
}

struct rule *rule_simple_command(void)
{
    struct rule *r = rule_init();
    struct test *t1 = test_rule_create(0, 0, RULE_ARG_LIST);
    struct test *t2 = test_rule_create(1, 0, RULE_REDIRECTION_LIST);
    test_add(t1, t2);
    rule_add_test(r, t1);
    //TODO: write this rule
    return r;
}

struct rule *rule_command(void)
{
    struct rule *r = rule_init();
    struct test *t1 = test_rule_create(0, 0, RULE_SIMPLE_COMMAND);

    rule_add_test(r, t1);
    //TODO: write this rule
    return r;
}
