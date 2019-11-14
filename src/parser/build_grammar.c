#include "parser.h"

struct test *test_tokens_create(int star, int plus, struct token *tok, ...)
{
    va_list tokens;
    va_start(tokens, tok);
    struct token_array *arr = token_array_init();
    while (tok)
    {
        token_array_add(arr, tok);
        tok = va_arg(tokens, struct token*);
    }
    va_end(tokens);
    struct test_props p = { .sub_test = NULL, .token_union = arr,
            .rule_id = RULE_NONE };
    struct test *res = test_init(TEST_TOKENS, &p, star, plus);
    return res;
}

struct test *test_rule_create(int star, int plus, enum rule_id id)
{
    struct test_props p = { .sub_test = NULL, .token_union = NULL,
            .rule_id = id };
    struct test *res = test_init(TEST_RULE, &p, star, plus);
    return res;
}

struct test *test_sub_create(int star, int plus, struct test *t, ...)
{
    va_list tests;
    va_start(tests, t);
    struct test *sub = t;
    while (t)
    {
        t->next = va_arg(t, struct test);
        t = t->next;
    }
    struct test_props p = { .sub_test = sub, token_union = NULL,
            .rule_id = id };
    struct test *res = test_init(TEST_PARENT, &p, star, plus);
    return res;
}
