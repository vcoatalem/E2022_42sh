#include "../parser.h"

struct rule *rule_element(void)
{
    struct rule *r = rule_init();
    
    struct test *t = test_tokens_create(0, 0, TOKEN_WORD);
    rule_add_test(r, t);

    return r;
}
