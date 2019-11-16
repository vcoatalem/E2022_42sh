#include "parser.h"

struct test_runner *test_runner_init(struct token_array *array, size_t pos)
{
    struct test_runner *tr = malloc(sizeof(struct test_runner));
    tr->state = STATE_NONE;
    tr->token_array = array;
    tr->pos = pos;
    tr->ast = NULL;
    return tr;
}

struct test_runner *test_runner_dup(struct test_runner *tr)
{
    struct test_runner *dup = test_runner_init(tr->token_array, tr->pos);
    dup->ast = ast_dup(tr->ast);
    return dup;
}

void test_runner_replace(struct test_runner **tr, struct test_runner *res)
{
    //test_runner_free(*tr);
    *tr = res;
}

int test_runner_is_over(struct test_runner *tr)
{
    return tr->pos >= tr->token_array->size;
}

//same as dup, except ast isnt copied
struct test_runner *test_runner_fork(struct test_runner *tr)
{
    struct test_runner *dup = test_runner_init(tr->token_array, tr->pos);
    return dup;
}

void test_runner_free(struct test_runner *tr)
{
    if (!tr)
        return;
    //ast_free(tr->ast);
    free(tr);
}
