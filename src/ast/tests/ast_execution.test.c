#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ast.h"

//use this to represent a command that succeeds
static struct ast *ast_command_should_succeed(void)
{
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_PIPE);

    struct ast *ast_cmd = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    ast_add_child(ast1, ast_cmd);

    struct ast *ast_redir = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd, ast_argv);
    ast_add_child(ast_cmd, ast_redir);

    struct ast *arg1 = ast_init(NODE_VALUE, "cat", OPERATOR_NONE);
    struct ast *arg2 = ast_init(NODE_VALUE, "foo", OPERATOR_NONE);
    ast_add_child(ast_argv, arg1);
    ast_add_child(ast_argv, arg2);
    return ast1;
}

//use this to represent a command that fails
static struct ast *ast_command_should_fail(void)
{
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_PIPE);

    struct ast *ast_cmd = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    ast_add_child(ast1, ast_cmd);

    struct ast *ast_redir = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd, ast_argv);
    ast_add_child(ast_cmd, ast_redir);

    struct ast *arg1 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *arg2 = ast_init(NODE_VALUE, "Hello", OPERATOR_NONE);
    struct ast *arg3 = ast_init(NODE_VALUE, "World!", OPERATOR_NONE);
    ast_add_child(ast_argv, arg1);
    ast_add_child(ast_argv, arg2);
    ast_add_child(ast_argv, arg3);
    return ast1;
}

int main(int argc, char **argv)
{

    struct ast *root = ast_init(NODE_OPERATOR, NULL, OPERATOR_AND);
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    if (q == 0)
    {
        //cat foo
        ast_add_child(root, ast_command_should_succeed());
    }
    else if (q == 1)
    {
        //echo Hello World
        ast_add_child(root, ast_command_should_fail());
    }
    ast_dot_print(root, "ast.dot");
    printf("%d\n", ast_execute(root));
    ast_free(root);
    return 0;
}
