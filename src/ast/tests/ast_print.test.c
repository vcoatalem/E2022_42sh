#include "../ast.h"
#include <stddef.h>

int main(void)
{
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_AND);
    struct ast *ast2 = ast_init(NODE_VALUE, "2", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "3", OPERATOR_NONE);
    struct ast *ast4 = ast_init(NODE_VALUE, "4", OPERATOR_NONE);
    struct ast *ast5 = ast_init(NODE_OPERATOR, "&", OPERATOR_OR);

    ast_add_child(ast2, ast3);
    ast_add_child(ast2, ast4);
    ast_add_child(ast1, ast2);
    ast_add_child(ast3, ast5);

    ast_dot_print(ast1);

    ast_free(ast1);

    return 0;
}
