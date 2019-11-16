#include "../ast.h"
#include "../../execution/execution.h"

int ast_handle_if(struct ast *ast)
{
    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;

    if ((ast->nb_children > 1)
            && (ast_execute(ast->forest[0]) == AST_SUCCESS))
        return ast_execute(ast->forest[1]);

    if (ast->nb_children > 2)
        return ast_execute(ast->forest[2]);

    return AST_ERROR;
}
