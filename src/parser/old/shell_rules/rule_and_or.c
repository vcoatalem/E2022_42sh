#include "../parser.h"

struct rule *rule_and(void)
{
    struct rule *r = rule_init();
    struct test *t1 = test_rule_create(0, 0, RULE_PIPELINE);
    
    struct test *next_1 = test_tokens_create(0, 0, TOKEN_DOUBLE_AMPERSAND,
            TOKEN_WORD);
    struct test *next_2 = test_tokens_create(1, 1, TOKEN_EOL);
    struct test *next_3 = test_rule_create(0, 0, RULE_PIPELINE);
    test_add(next_1, next_2);
    test_add(next_2, next_3);

    struct test *t2 = test_sub_create(1, 1, next_1);
    test_add(t1, t2);

    rule_add_test(r, t1);
    return r;
}

struct rule *rule_or(void)
{
    struct rule *r = rule_init();
    struct test *t1 = test_rule_create(0, 0, RULE_PIPELINE);
    
    struct test *next_1 = test_tokens_create(0, 0, TOKEN_DOUBLE_PIPE,
            TOKEN_WORD);
    struct test *next_2 = test_tokens_create(1, 1, TOKEN_EOL);
    struct test *next_3 = test_rule_create(0, 0, RULE_PIPELINE);
    test_add(next_1, next_2);
    test_add(next_2, next_3);

    struct test *t2 = test_sub_create(1, 1, next_1);
    test_add(t1, t2);

    rule_add_test(r, t1);
    //TODO: write this rule
    return r;
}

struct rule *rule_and_or(void)
{
    struct rule *r = rule_init();
    struct test *t1 = test_rule_create(0, 0, RULE_AND);
    struct test *t2 = test_rule_create(0, 0, RULE_OR);
    rule_add_test(r, t1);
    rule_add_test(r, t2);
    return r;
}
