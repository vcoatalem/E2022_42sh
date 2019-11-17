#include "../ast.h"
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{
    /* PIPE
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_PIPE);
    struct ast *ast2 = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);

    struct ast *arg1 = ast_init(NODE_VALUE, "cat", OPERATOR_NONE);
    struct ast *arg2 = ast_init(NODE_VALUE, "foo", OPERATOR_NONE);
    ast_add_child(ast3, arg1);
    ast_add_child(ast3, arg2);

    ast_add_child(ast2, ast3);
    ast_add_child(ast1, ast2);

    printf("%d\n", ast_handle_pipe(ast1));

    ast_free(ast1);
    */

    ///* IF
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_IF);

    struct ast *ast2 = ast_init(NODE_VALUE, "2", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "==", OPERATOR_NONE);
    struct ast *ast4 = ast_init(NODE_VALUE, "2", OPERATOR_NONE);

    struct ast *ast5 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *ast6 = ast_init(NODE_VALUE, "bar", OPERATOR_NONE);

    ast_add_child(ast3, ast4);
    ast_add_child(ast2, ast3);
    ast_add_child(ast1, ast2);

    ast_add_child(ast5, ast6);
    ast_add_child(ast1, ast5);

    printf("%d\n", ast_handle_if(ast1));

    ast_free(ast1);

    //*/

    /* WHILE
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_WHILE);

    struct ast *ast2 = ast_init(NODE_VALUE, "i", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "+", OPERATOR_NONE);
    struct ast *ast4 = ast_init(NODE_VALUE, "+", OPERATOR_NONE);
    struct ast *ast5 = ast_init(NODE_VALUE, "<", OPERATOR_NONE);
    struct ast *ast6 = ast_init(NODE_VALUE, "20", OPERATOR_NONE);

    struct ast *ast7 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *ast8 = ast_init(NODE_VALUE, "bar", OPERATOR_NONE);

    ast_add_child(ast3, ast4);
    ast_add_child(ast2, ast3);
    ast_add_child(ast5, ast6);
    ast_add_child(ast2, ast5);
    ast_add_child(ast1, ast2);

    ast_add_child(ast5, ast6);
    ast_add_child(ast1, ast5);

    printf("%d\n", ast_handle_while(ast1));

    ast_free(ast1);
    */

    return 0;
}
