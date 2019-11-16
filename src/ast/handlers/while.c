#include "../ast.h"
#include "../../execution/execution.h"

int ast_handle_while(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;

    while (try_execute == AST_ERROR)
    {
        try_execute = ast_execute(ast->forest[0]);
    }

    return try_execute;
}
