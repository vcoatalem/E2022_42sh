#include "ast.h"

int ast_handle_until(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;

    while ((try_execute = ast_execute(ast->forest[0])) == AST_ERROR)
    {
        for (size_t i = 1; i < ast->nb_children; i++)
            ast_execute(ast->forest[i]);
    }

    return try_execute;
}
