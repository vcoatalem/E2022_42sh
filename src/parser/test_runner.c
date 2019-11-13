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
    dup->ast = ast_dup(tr->ast);
    return dup;
}

void test_runner_free(struct test_runner *tr)
{
    ast_free(tr->ast);
    free(tr);
}
