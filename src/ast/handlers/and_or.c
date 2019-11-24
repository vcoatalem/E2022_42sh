#include "ast.h"
#include "../../main/42sh.h"

int ast_handle_and_or(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    struct ast *pipeline = find_op_type(ast, OPERATOR_PIPE);
    struct ast *next = find_op_type(ast, OPERATOR_AND);
    struct ast *operator_and_concat = NULL;
    struct ast *operator_or_concat = NULL;
    if (next)
    {
        operator_and_concat = find_op_type(next, OPERATOR_AND);
        operator_or_concat = find_op_type(next, OPERATOR_OR);
    }

    int try_execute = ast_execute(pipeline, bundle_ptr);
    if (operator_and_concat && try_execute == AST_SUCCESS)
    {
        try_execute = ast_handle_and_or(find_op_type(operator_and_concat,
                OPERATOR_AND), bundle_ptr);
    }
    else if (operator_or_concat && try_execute == AST_ERROR)
    {
        try_execute = ast_handle_and_or(find_op_type(operator_or_concat,
                OPERATOR_AND), bundle_ptr);
    }
    return try_execute;
}
