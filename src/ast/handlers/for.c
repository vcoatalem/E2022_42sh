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

    while (try_execute == AST_SUCCESS)
    {
        try_execute = ast_execute(ast_for_body, bundle);
        if (try_execute == AST_SUCCESS)
        {
            return_execute = ast_execute(ast_do, bundle);
        }
    }
    return return_execute;
}
