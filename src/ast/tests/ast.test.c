#include "../ast.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    struct ast *ast1 = ast_init(NODE_VALUE, "1", OPERATOR_NONE);
    struct ast *ast2 = ast_init(NODE_VALUE, "2", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "3", OPERATOR_NONE);
    struct ast *ast4 = ast_init(NODE_VALUE, "4", OPERATOR_NONE);

    ast_add_child(ast2, ast3);
    ast_add_child(ast2, ast4);
    ast_add_child(ast1, ast2);

    assert(ast1->nb_children == 1);
    assert(ast2->nb_children == 2);

    ast_free(ast1);

    return 0;
}
