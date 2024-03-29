#include "ast.h"
#include "../../main/42sh.h"

static int ast_handle_or(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct ast *ast_pipe = find_op_type(ast, OPERATOR_PIPE);
    struct ast *ast_or = find_op_type(ast, OPERATOR_OR);

    int return_value = ast_execute(ast_pipe, bundle_ptr);
    if (return_value == AST_ERROR && ast_or)
    {
        if (bundle->ast_traversal_context.loop_depth
            && (bundle->ast_traversal_context.found_break
                || bundle->ast_traversal_context.found_continue))
        {
            //break / continue
            return return_value;
        }
        //compute next node
        return_value = ast_handle_or(ast_or, bundle_ptr);
    }
    return return_value;
}

int ast_handle_and_or(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;
    struct ast *and_concat = find_op_type(ast, OPERATOR_AND);
    struct ast *or_concat = find_op_type(ast, OPERATOR_OR);
    struct ast *ast_pipe = find_op_type(ast, OPERATOR_PIPE);
    struct ast *or = or_concat ? find_op_type(or_concat, OPERATOR_OR) : NULL;
    struct ast *and_or = and_concat ?
            find_op_type(and_concat, OPERATOR_AND) : NULL;
    int return_value = ast_execute(ast_pipe, bundle_ptr);
    if (bundle->shopt->debug)
    {
        printf("[AST EXECUTION] AND node received: %d\n", return_value);
    }
    if (or && return_value != AST_SUCCESS)
    {
        return_value = ast_handle_or(or, bundle_ptr);
        //TODO: add break/continue there ?
    }
    if (and_or && return_value == AST_SUCCESS)
    {
        return_value = ast_handle_and_or(and_or, bundle_ptr);
        if (bundle->ast_traversal_context.loop_depth
            && (bundle->ast_traversal_context.found_break
                || bundle->ast_traversal_context.found_continue))
        {
            return return_value;
        }
    }
    return return_value;
}
