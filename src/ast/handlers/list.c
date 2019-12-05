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
        ast_execute(ast->forest[i], bundle);
        //loop break/continue handlers
        if (bundle->ast_traversal_context.found_break)
        {
            //bundle->ast_traversal_context.found_break = 0;
            break;
        }
        if (bundle->ast_traversal_context.found_continue)
        {
            //bundle->ast_traversal_context.found_continue = 0;
            //continue;
            break;
        }
    }

    return try_execute;
}
