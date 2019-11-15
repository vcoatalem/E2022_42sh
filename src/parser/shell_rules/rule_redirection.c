#include "../parser.h"

struct rule *rule_ionumber(void)
{
    struct rule *r = rule_init();

    struct test *t = test_tokens_create(0, 0, TOKEN_STDIN, TOKEN_STDOUT,
            TOKEN_STDERR);
    rule_add_test(r, t);
    return r;
}

struct rule *rule_redirection_symbol(void)
{
    struct rule *r = rule_init();
    struct test *t = test_tokens_create(0, 0, TOKEN_LESS, TOKEN_GREAT,
            TOKEN_DOUBLE_LESS, TOKEN_DOUBLE_GREAT, TOKEN_DOUBLE_LESS_DASH,
            TOKEN_GREAT_AMPERSAND, TOKEN_LESS_AMPERSAND, TOKEN_GREAT_PIPE,
            TOKEN_LESS_GREAT, TOKEN_WORD);
    //in this case, token_word used to close the va_list
    rule_add_test(r, t);
    return r;
}

struct rule *rule_redirection(void)
{
    struct rule *r = rule_init();

    struct test *t1 = test_rule_create(1, 0, RULE_IONUMBER);
    struct test *t2 = test_rule_create(0, 0, RULE_REDIRECTION_SYMBOL);
    struct test *t3 = test_rule_create(0, 0, RULE_ELEMENT);

    test_add(t1, t2);
    test_add(t2, t3);
    rule_add_test(r, t1);
    return r;
}
