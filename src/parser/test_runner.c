#include "parser.h"

struct test_runner *test_runner_init(struct token_array *array, size_t pos)
{
    struct test_runner *tr = malloc(sizeof(struct test_runner));
    tr->token_array = array;
    tr->pos = pos;
    tr->ast = NULL;
    return tr;
}

struct test_runner *test_runner_dup(struct test_runner *tr)
{
    struct test_runner *dup = malloc(sizeof(struct test_runner));
    dup->token_array = tr->token_array;
    dup->pos = tr->pos;
    dup->ast = NULL;//ast_dup(tr->ast);
    return dup;
}

void test_runner_free(struct test_runner *tr)
{
    ast_free(tr->ast);
    free(tr);
}

static int test_execute_token_union(struct test *test,
        struct test_runner *runner)
{
    struct token_array *tok_union = test->props.token_union;
    struct token *current = *(runner->token_array->token_arr + runner->pos);
    for (size_t i = 0; i < tok_union; i++)
    {
        if (current->type == (*(tok_union->token_arr + i))->type)
        {
            runner->pos++;
            return PARSE_SUCCESS;
        }
    }
    return PARSE_FAILURE;
}
//


static int test_execute_rule(struct test *test,
        struct test_runner *runner, struct grammar *grammar)
{
    struct rule *target_rule = *(grammar->rules + test->props.rule_id);
    return rule_execute(target_rule, runner, grammar);
}

//

static int test_execute_sub_test(struct test *test,
        struct test_runner *runner, struct grammar *grammar)
{
    return test_execute(test->props.sub_test, runner, grammar);
}

int test_execute(struct test *test, struct test_runner *runner,
        struct grammar *grammar)
{
    int val = 0;
    switch(test->type)
    {
        case TEST_PARENT:
            val = test_execute_sub_test(test, runner, grammar);
            break;
        case TEST_TOKEN:
            val = test_execute_token_union(test, runner);
            break;
        case TEST_RULE:
            val = test_execute_rule(test, runner, grammar);
            break;
        case default:
            val = PARSE_SUCCESS;
    }
    return val;
}
