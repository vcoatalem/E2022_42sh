#include "parser.h"

struct test *test_init(enum test_type type, struct test_props props, int star,
        int plus)
{
    struct test *res = calloc(1, sizeof(struct test));
    res->type = type;
    res->props.sub_test = props.sub_test;
    res->props.token = props.token;
    res->props.rule_id = props.rule_id;
    res->star = star;
    res->plus = plus;
    return res;
}

void test_free(struct test *test)
{
    if (!test)
        return;
    test_free(test->next);
    if (test->type == TEST_PARENT)
    {
        test_free(test->props.sub_test);
    }
    else if (test->type == TEST_TOKEN)
    {
        token_list_free(test->props.token);
    }
    free(test);
}
