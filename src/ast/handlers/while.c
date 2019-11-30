#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_while(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;
    int return_value = AST_ERROR;

    struct ast *ast_while_body = find_op_type(ast, OPERATOR_LIST);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);

    if (ast_while_body == NULL || ast_do == NULL)
        return AST_MISSING_ARG;

    bundle->ast_traversal_context.loop_depth++;
    while (try_execute == AST_SUCCESS)
    {
        try_execute = ast_execute(ast_while_body, bundle_ptr);
        return_value = ast_execute(find_op_type(ast_do, OPERATOR_LIST),
                bundle_ptr); 
        
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
    bundle->ast_traversal_context.loop_depth--;
    return return_value;
}
