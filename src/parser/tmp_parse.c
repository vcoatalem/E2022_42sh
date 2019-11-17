#include "parser.h"


struct ast *tmp_parse(struct token_array *arr)
{
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_PIPE);
    
    struct ast *ast_cmd = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    ast_add_child(ast1, ast_cmd);
    
    struct ast *ast_redir = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd, ast_argv);
    ast_add_child(ast_cmd, ast_redir);

    for (size_t i = 0; i < arr->size - 1; ++i)
    {
        ast_add_child(ast_argv, ast_init(NODE_VALUE, arr->tok_array[i]->value, OPERATOR_NONE));
    }
    return ast1;
}