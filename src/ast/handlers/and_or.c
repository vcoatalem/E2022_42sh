#include "ast.h"

int ast_handle_and(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i]) == AST_ERROR)
            try_execute = AST_ERROR;
    }

    return try_execute;
}

int ast_handle_or(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i]) == AST_SUCCESS)
            try_execute = AST_SUCCESS;
    }

    return try_execute;
}
