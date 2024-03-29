#include "ast.h"
#include "../main/42sh.h"

operator_handler get_operator_handler(enum operator_type type)
{
    if (type == OPERATOR_AND)
        return ast_handle_and_or;
    else if (type == OPERATOR_LIST)
        return ast_handle_list;
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
    else if (type == OPERATOR_FUNC_DECLARATION)
        return ast_handle_funcdec;
    else if (type == OPERATOR_VAR_DECLARATION)
        return ast_handle_vardec;
    else if (type == OPERATOR_CASE)
        return ast_handle_case;
    else
        return NULL;
}

int ast_execute(struct ast *ast, void *bundle_ptr)
{
    if(!ast || !bundle_ptr)
        return AST_ERROR;
    struct execution_bundle *bundle = bundle_ptr;
    if (ast->node_type == NODE_VALUE)
    {
        return AST_SUCCESS;
    }
    operator_handler handler = get_operator_handler(ast->op_type);
    int return_val = handler(ast, bundle);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[AST EXECUTION] ast_execute for ast of operator type");
        printf("%d and value `%s` returning: %d\n",
                ast->op_type, ast->value, return_val);
    }
    return return_val;
}
