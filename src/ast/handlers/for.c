#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_for(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;
    int return_execute = AST_ERROR;

    struct ast *ast_for_body = find_op_type(ast, OPERATOR_AND);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);

    if (ast_for_body == NULL || ast_do == NULL)
        return AST_MISSING_ARG;

    bundle->ast_traversal_context.loop_depth++;
    while (try_execute == AST_SUCCESS)
    {
        try_execute = ast_execute(ast_for_body, bundle);
        if (try_execute == AST_SUCCESS)
        {
            return_execute = ast_execute(find_op_type(ast_do, OPERATOR_LIST),
                    bundle);
            
            //loop break/continue handlers
            if (bundle->ast_traversal_context.found_break)
            {
                bundle->ast_traversal_context.found_break = 0;
                break;
            }
            if (bundle->ast_traversal_context.found_continue)
            {
                bundle->ast_traversal_context.found_continue = 0;
                continue;
            }
        }
    }
    bundle->ast_traversal_context.loop_depth--;
    return return_execute;
}
