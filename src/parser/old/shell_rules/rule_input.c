#include "../parser.h"

struct rule *rule_input(void)
{
    struct rule *r = rule_init();
    struct test *a1 = test_rule_create(0, 0, RULE_LIST);
    struct test *a2 = test_tokens_create(0, 0, TOKEN_EOL, TOKEN_WORD);
    test_add(a1, a2);
    rule_add_test(r, a1);

    struct test *b1 = test_rule_create(0, 0, RULE_LIST);
    struct test *b2 = test_tokens_create(0, 0, TOKEN_EOF, TOKEN_WORD);
    test_add(b1, b2);
    rule_add_test(r, b1);

    struct test *c1 = test_tokens_create(0, 0, TOKEN_EOL, TOKEN_WORD);
    rule_add_test(r, c1);

    struct test *d1 = test_tokens_create(0, 0, TOKEN_EOF, TOKEN_WORD);
    rule_add_test(r, d1);
    return r;
}
