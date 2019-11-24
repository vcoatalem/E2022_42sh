#include "ast.h"
#include "../../main/42sh.h"

int ast_handle_list(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;
    for (long int i = ast->nb_children - 1; i >= 0; i--)
    {
        try_execute = ast_execute(ast->forest[i], bundle);
        if (try_execute != AST_SUCCESS)
            break;
    }

    return try_execute;
}
