#include "ast.h"
#include "../../main/42sh.h"

int ast_handle_and(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i], bundle) == AST_ERROR)
            try_execute = AST_ERROR;
    }

    return try_execute;
}

int ast_handle_or(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i], bundle) == AST_SUCCESS)
            try_execute = AST_SUCCESS;
    }

    return try_execute;
}
