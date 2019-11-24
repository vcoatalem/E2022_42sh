#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_if(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;

    struct ast *ast_if_body = find_op_type(ast, OPERATOR_AND);
    struct ast *ast_then = find_op_type(ast, OPERATOR_THEN);
    if (ast_if_body == NULL || ast_then == NULL)
        return AST_ERROR;

    if (ast_execute(ast_if_body, bundle) == AST_SUCCESS)
        return ast_execute(ast_then->forest[0], bundle);

    struct ast *ast_else = find_op_type(ast, OPERATOR_ELSE);
    if (ast_else == NULL)
        return AST_ERROR;
    return ast_execute(ast_else->forest[0], bundle);
}
