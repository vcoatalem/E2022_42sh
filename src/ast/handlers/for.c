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

    struct ast *ast_for_body = find_op_type(ast, OPERATOR_FOR_BODY);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);

    while (try_execute == AST_SUCCESS)
    {
        try_execute = ast_execute(ast_for_body, bundle);
        ast_execute(ast_do, bundle);
    }

    struct ast *ast_done = find_op_type(ast, OPERATOR_DONE);
    return ast_execute(ast_done, bundle);
}
