#include "../parser.h"

struct rule *rule_pipeline(void)
{
    struct rule *r = rule_init();

    struct test *t1 = test_tokens_create(1, 0, TOKEN_EXCLAMATION_POINT);
    struct test *t2 = test_rule_create(0, 0, RULE_COMMAND);
    test_add(t1, t2);

    struct test *next1 = test_tokens_create(0, 0, TOKEN_PIPE);
    struct test *next2 = test_tokens_create(1, 1, TOKEN_EOL);
    struct test *next3 = test_rule_create(0, 0, RULE_COMMAND);
    test_add(next1, next2);
    test_add(next2, next3);

    struct test *t3 = test_sub_create(1, 1, next1);
    test_add(t2, t3);

    rule_add_test(r, t1);
    return r;
}
