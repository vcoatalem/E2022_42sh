#include "../ast.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    /*
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
    */

    struct ast *ast1 = ast_init("arg_list", OPERATOR_NONE);
    struct ast *ast2 = ast_init("echo", OPERATOR_NONE);
    struct ast *ast3 = ast_init("arg_list", OPERATOR_NONE);
    struct ast *ast4 = ast_init("Hello", OPERATOR_NONE);
    struct ast *ast5 = ast_init("arg_list", OPERATOR_NONE);
    struct ast *ast6 = ast_init(NULL, OPERATOR_NONE);

    ast_add_child(ast5, ast6);
    ast_add_child(ast3, ast4);
    ast_add_child(ast3, ast5);
    ast_add_child(ast1, ast2);
    ast_add_child(ast1, ast3);

    ast_dot_print(ast1, "ast.dot");

    char **arg_list = get_arg_list(ast1);
    for (int i = 0; i < 2; i++)
        printf("%s\n", arg_list[i]);

    ast_free(ast1);

    return 0;
}
