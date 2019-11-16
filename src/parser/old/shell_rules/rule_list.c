#include "../parser.h"

struct rule *rule_list(void)
{
    struct rule *r = rule_init();

    struct test *t1 = test_rule_create(0, 0, RULE_AND_OR);

    struct test *next1 = test_tokens_create(0, 0, TOKEN_SEMI_COLON,
            TOKEN_AMPERSAND, TOKEN_WORD);
    struct test *next2 = test_rule_create(0, 0, RULE_AND_OR);
    test_add(next1, next2);

    struct test *t2 = test_sub_create(1, 1, next1);
    test_add(t1, t2);

    struct test *t3 = test_tokens_create(1, 0, TOKEN_SEMI_COLON,
        TOKEN_AMPERSAND, TOKEN_WORD);
    test_add(t2, t3);
    rule_add_test(r, t1);
    return r;
}
