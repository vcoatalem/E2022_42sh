#include "ast.h"

operator_handler get_operator_handler(enum operator_type type)
{
    if (type == OPERATOR_AND)
        return ast_handle_and;
    else if (type == OPERATOR_OR)
        return ast_handle_or;
    else if (type == OPERATOR_PIPE)
         return ast_handle_pipe;
    else
        return NULL;
}

int ast_execute(struct ast *ast)
{
    if (ast->node_type == NODE_VALUE)
    {
        return AST_SUCCESS;
    }
    operator_handler handler = get_operator_handler(ast->content.op_type);
    return handler(ast);
}
