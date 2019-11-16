#include "../ast.h"
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_PIPE);
    struct ast *ast3 = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);

    struct ast *arg1 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *arg2 = ast_init(NODE_VALUE, "Hello!", OPERATOR_NONE);
    ast_add_child(ast3, arg1);
    ast_add_child(ast3, arg2);

    ast_add_child(ast1, ast3);

    ast_handle_pipe(ast1);

    ast_free(ast1);

    return 0;
}
