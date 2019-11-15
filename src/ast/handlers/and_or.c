#include "ast.h"

int ast_handle_and(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        int try_execute = ast_execute(ast->forest[i]);
        if (try_execute != AST_SUCCESS)
            return try_execute;
    }
    return AST_SUCCESS;
}

int ast_handle_or(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;
    int try_execute = AST_ERROR;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        try_execute = ast_execute(ast->forest[i]);
        if (try_execute == AST_SUCCESS)
            return try_execute;
    }
    return try_execute;
}
