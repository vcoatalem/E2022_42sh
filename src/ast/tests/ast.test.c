#include "../ast.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    struct ast *ast1 = ast_init(NODE_VALUE, "1", OPERATOR_NONE);
    struct ast *ast2 = ast_init(NODE_VALUE, "2", OPERATOR_NONE);
    struct ast *ast3 = ast_init(NODE_VALUE, "3", OPERATOR_NONE);
    struct ast *ast4 = ast_init(NODE_OPERATOR, NULL, OPERATOR_AND);

    ast_add_child(ast2, ast3);
    ast_add_child(ast2, ast4);
    ast_add_child(ast1, ast2);

    struct ast *dup1 = ast_dup(ast1);

    struct ast *clean1 = ast_init(NODE_VALUE, NULL, OPERATOR_NONE);
    ast_add_child(ast3, clean1);

    assert(ast1->nb_children == 1);
    assert(ast2->nb_children == 2);

    assert(dup1->nb_children == 1);
    assert(dup1->forest[0]->nb_children == 2);

    ast_dot_print(ast1, "ast.dot");
    ast_dot_print(dup1, "ast_dup.dot");

    ast_free(ast1);
    ast_free(dup1);

    return 0;
}
