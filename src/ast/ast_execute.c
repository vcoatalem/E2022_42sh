#include "ast.h"

operator_handler get_operator_handler(enum operator_type type)
{
    if (type == OPERATOR_AND)
        return ast_handle_and;
    else if (type == OPERATOR_OR)
        return ast_handle_or;
    else if (type == OPERATOR_PIPE)
         return ast_handle_pipe;
    else if (type == OPERATOR_IF)
        return ast_handle_if;
    else if (type == OPERATOR_WHILE)
        return ast_handle_while;
    else if (type == OPERATOR_FOR)
        return ast_handle_for;
    else if (type == OPERATOR_UNTIL)
        return ast_handle_until;
    else
        return NULL;
}

int ast_execute(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    printf("[AST] entered ast_execute for ast of operator type %d and value `%s`\n", ast->op_type, ast->value);
    if (ast->node_type == NODE_VALUE)
    {
        return AST_SUCCESS;
    }
    operator_handler handler = get_operator_handler(ast->op_type);
    return handler(ast, bundle);
}
