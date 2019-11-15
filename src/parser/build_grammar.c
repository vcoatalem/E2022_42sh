
#include "parser.h"

struct test *test_tokens_create(int optionnal, int repeatable,
        enum token_type tok, ...)
{
    struct token_array *arr = token_array_init();
    if (tok == TOKEN_WORD)
    {
        token_array_add(arr, token_init(TOKEN_WORD, ""));
    }
    else
    {
        va_list tokens; 
        va_start(tokens, tok);
        while (tok)
        {
            token_array_add(arr, token_init(tok, token_to_string(tok)));
            tok = va_arg(tokens, enum token_type);
        }
        va_end(tokens);
    }
    struct test_props p = { .sub_test = NULL, .token_union = arr,
            .rule_id = RULE_NONE };
    struct test *res = test_init(TEST_TOKEN, &p, optionnal, repeatable);
    return res;
}

struct test *test_rule_create(int optionnal, int repeatable, enum rule_id id)
{
    struct test_props p = { .sub_test = NULL, .token_union = NULL,
            .rule_id = id };
    struct test *res = test_init(TEST_RULE, &p, optionnal, repeatable);
    return res;
}

struct test *test_sub_create(int optionnal, int repeatable, struct test *t, ...)
{
    va_list tests;
    va_start(tests, t);
    struct test *sub = t;
    while (t)
    {
        t->next = va_arg(tests, struct test*);
        t = t->next;
    }
    struct test_props p = { .sub_test = sub, .token_union = NULL,
            .rule_id = RULE_NONE };
    struct test *res = test_init(TEST_PARENT, &p, optionnal, repeatable);
    return res;
}
