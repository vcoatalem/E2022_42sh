#include "../ast.h"
#include "../../execution/execution.h"

int ast_handle_while(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;

    while ((try_execute = ast_execute(ast->forest[0])) == AST_SUCCESS)
    {
        for (size_t i = 1; i < ast->nb_children; i++)
            ast_execute(ast->forest[i]);
    }

    if (try_execute == AST_ERROR)
        return AST_SUCCESS;

    return AST_ERROR;
}
