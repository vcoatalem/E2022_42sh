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

    struct ast *ast_until_body = find_op_type(ast, OPERATOR_UNTIL_BODY);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);

    while (try_execute == AST_ERROR)
    {
        try_execute = ast_execute(ast_until_body, bundle);
        ast_execute(ast_do, bundle);
    }

    struct ast *ast_done = find_op_type(ast, OPERATOR_DONE);
    return ast_execute(ast_done, bundle);
}
