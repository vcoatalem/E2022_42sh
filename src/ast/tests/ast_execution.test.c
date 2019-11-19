#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ast.h"

//use this to represent a command that succeeds
static struct ast *ast_command_should_succeed(void)
{
    /* PIPE
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
    */

    ///* IF
    struct ast *ast1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_IF);

    struct ast *ast_if_body = ast_init(NODE_OPERATOR, "if_body", OPERATOR_IF_BODY);
    struct ast *ast_then = ast_init(NODE_OPERATOR, "then", OPERATOR_THEN);
    struct ast *ast_else = ast_init(NODE_OPERATOR, "else", OPERATOR_ELSE);
    ast_add_child(ast1, ast_if_body);
    ast_add_child(ast1, ast_then);
    ast_add_child(ast1, ast_else);

    struct ast *ast_cmd_if = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    struct ast *ast_cmd_then = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    struct ast *ast_cmd_else = ast_init(NODE_VALUE, "cmd", OPERATOR_NONE);
    ast_add_child(ast_if_body, ast_cmd_if);
    ast_add_child(ast_then, ast_cmd_then);
    ast_add_child(ast_else, ast_cmd_else);

    struct ast *ast_redir_if = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv_if = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd_if, ast_redir_if);
    ast_add_child(ast_cmd_if, ast_argv_if);

    struct ast *ast_redir_then = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv_then = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd_then, ast_redir_then);
    ast_add_child(ast_cmd_then, ast_argv_then);

    struct ast *ast_redir_else = ast_init(NODE_VALUE, "redir", OPERATOR_NONE);
    struct ast *ast_argv_else = ast_init(NODE_VALUE, "argv", OPERATOR_NONE);
    ast_add_child(ast_cmd_else, ast_redir_else);
    ast_add_child(ast_cmd_else, ast_argv_else);

    struct ast *arg1 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *arg2 = ast_init(NODE_VALUE, "Hello", OPERATOR_NONE);
    //struct ast *redir_arg1 = ast_init(NODE_OPERATOR, NULL, OPERATOR_NONE);
    ast_add_child(ast_argv_if, arg1);
    ast_add_child(ast_argv_if, arg2);
    //ast_add_child(ast_redir_if, redir_arg1);

    struct ast *arg3 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *arg4 = ast_init(NODE_VALUE, "World!", OPERATOR_NONE);
    //struct ast *redir_arg2 = ast_init(NODE_OPERATOR, NULL, OPERATOR_NONE);
    ast_add_child(ast_argv_then, arg3);
    ast_add_child(ast_argv_then, arg4);
    //ast_add_child(ast_redir_then, redir_arg2);

    struct ast *arg5 = ast_init(NODE_VALUE, "echo", OPERATOR_NONE);
    struct ast *arg6 = ast_init(NODE_VALUE, "there!", OPERATOR_NONE);
    //struct ast *redir_arg3 = ast_init(NODE_OPERATOR, NULL, OPERATOR_NONE);
    ast_add_child(ast_argv_else, arg5);
    ast_add_child(ast_argv_else, arg6);
    //ast_add_child(ast_redir_else, redir_arg3);
    //*/

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
