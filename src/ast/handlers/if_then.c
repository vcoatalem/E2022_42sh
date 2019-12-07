#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_if(struct ast *ast, void *bundle_ptr)
{
    struct ast *ast_if_body = find_op_type(ast, OPERATOR_LIST);
    struct ast *ast_then = find_op_type(ast, OPERATOR_THEN);
    struct ast *ast_then_body = ast_then ? 
            find_op_type(ast_then, OPERATOR_LIST) : NULL;
    struct ast *ast_else = ast_then ?
            find_op_type(ast_then, OPERATOR_ELSE) : NULL;
    int try_execute = ast_execute(ast_if_body, bundle_ptr);
    if (try_execute == AST_SUCCESS)
    {
        if (ast_then && ast_then_body)
        {
            try_execute = ast_execute(ast_then_body, bundle_ptr);
        }
    }
    else
    {
        if (ast_else)
        {
            try_execute = ast_handle_if(ast_else, bundle_ptr);
        }
    }
    return try_execute;
}
