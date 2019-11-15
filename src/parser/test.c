#include <stdarg.h>

#include "parser.h"

struct test *test_init(enum test_type type, struct test_props *props,
        int optionnal, int repeatable)
{
    struct test *res = calloc(1, sizeof(struct test));
    res->type = type;
    res->props.sub_test = props->sub_test;
    res->props.token_union = props->token_union;
    res->props.rule_id = props->rule_id;
    res->optionnal = optionnal;
    res->repeatable = repeatable;
    return res;
}

void test_add(struct test *test, struct test *res)
{
    test->next = res;
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
        token_array_free(test->props.token_union);
    }
    free(test);
}

void test_print(struct test *test, FILE *out)
{
    fprintf(out, "[ type %d ", test->type);
    if (test->type == TEST_RULE)
    {
        fprintf(out, " rule_id: %d", test->props.rule_id);
    }
    else if (test->type == TEST_PARENT)
    {
        test_print(test->props.sub_test, out);
    }
    else if (test->type == TEST_TOKEN)
    {
        struct token_array *arr = test->props.token_union;
        fprintf(out, " tokens: ("); 
        for (size_t i = 0; i < arr->size; i++)
        {
            fprintf(out, "`%s`|", token_to_string(arr->tok_array[i]->type));
        }
    }
    fprintf(out, " ]");
    if (test->optionnal && !test->repeatable)
        fprintf(out, "!");
    if (test->optionnal && test->repeatable)
        fprintf(out, "*");
    else if (!test->optionnal && test->repeatable)
        fprintf(out, "+");
    if (test->next)
    {
        fprintf(out, " -> ");
        test_print(test->next, out);
    }
}
