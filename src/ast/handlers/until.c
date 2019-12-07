#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_until(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;
    int return_value = AST_ERROR;

    struct ast *ast_until_body = find_op_type(ast, OPERATOR_UNTIL);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);

    if (ast_until_body == NULL || ast_do == NULL)
        return AST_MISSING_ARG;

    bundle->ast_traversal_context.loop_depth++;
    while (try_execute == AST_ERROR)
    {
        if (bundle->ast_traversal_context.found_continue)
        {
            bundle->ast_traversal_context.found_continue -= 1;
            continue;
        }
        try_execute = ast_execute(ast_until_body, bundle);
        return_value = ast_execute(find_op_type(ast_do, OPERATOR_LIST),
                bundle);

        //loop break/continue handlers
        if (bundle->ast_traversal_context.found_break)
        {
            bundle->ast_traversal_context.found_break -= 1;
            break;
        }
        if (bundle->ast_traversal_context.found_continue)
        {
            bundle->ast_traversal_context.found_continue -= 1;
            continue;
        }
    }
    bundle->ast_traversal_context.loop_depth--;
    return return_value;
}
