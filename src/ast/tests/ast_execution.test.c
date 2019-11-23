#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../main/42sh.h"
#include "../ast.h"

static struct ast *ast_arg_list(void)
{
    struct ast *ast_args = ast_init("args", OPERATOR_ARG_LIST);
    struct ast *ast_next1 = ast_init("args", OPERATOR_ARG_LIST);
    struct ast *ast_next2 = ast_init("args", OPERATOR_ARG_LIST);
    struct ast *ast_arg1 = ast_init("arg1", OPERATOR_GET_VALUE);
    struct ast *ast_arg2 = ast_init("arg2", OPERATOR_GET_VALUE);
    struct ast *ast_arg3 = ast_init("arg3", OPERATOR_GET_VALUE);
    struct ast *arg1 = ast_init("echo", OPERATOR_NONE);
    struct ast *arg2 = ast_init("A", OPERATOR_NONE);
    struct ast *arg3 = ast_init("B", OPERATOR_NONE);
    ast_add_child(ast_args, ast_next1);
    ast_add_child(ast_next1, ast_next2);
    ast_add_child(ast_args, ast_arg1);
    ast_add_child(ast_next1, ast_arg2);
    ast_add_child(ast_next2, ast_arg3);
    ast_add_child(ast_arg1, arg1);
    ast_add_child(ast_arg2, arg2);
    ast_add_child(ast_arg3, arg3);
    return ast_args;
}

static struct ast *ast_redir_A(void)
{
    struct ast *ast_redir = ast_init("redir", OPERATOR_REDIR);
    struct ast *ast_to = ast_init("redir_to", OPERATOR_GET_REDIR_TO);
    struct ast *ast_symbol = ast_init("redir_symbol", OPERATOR_GET_REDIR_SYMBOL);
    struct ast *ast_ionumber = ast_init("redir_ionumber", OPERATOR_GET_IONUMBER);

    ast_add_child(ast_redir, ast_to);
    ast_add_child(ast_redir, ast_symbol);
    ast_add_child(ast_redir, ast_ionumber);

    struct ast *ast_ionumber_val = ast_init("0", OPERATOR_NONE);
    struct ast *ast_symbol_val = ast_init(">", OPERATOR_NONE);
    struct ast *ast_to_val = ast_init("output", OPERATOR_NONE);


    ast_add_child(ast_to, ast_to_val);
    ast_add_child(ast_symbol, ast_symbol_val);
    ast_add_child(ast_ionumber, ast_ionumber_val);

    return ast_redir;
}

static struct ast *ast_redir_B(void)
{
    struct ast *ast_redir = ast_init("redir", OPERATOR_REDIR);
    struct ast *ast_to = ast_init("redir_to", OPERATOR_GET_REDIR_TO);
    struct ast *ast_symbol = ast_init("redir_symbol", OPERATOR_GET_REDIR_SYMBOL);

    ast_add_child(ast_redir, ast_to);
    ast_add_child(ast_redir, ast_symbol);

    struct ast *ast_symbol_val = ast_init(">", OPERATOR_NONE);
    struct ast *ast_to_val = ast_init("output", OPERATOR_NONE);

    ast_add_child(ast_to, ast_to_val);
    ast_add_child(ast_symbol, ast_symbol_val);

    return ast_redir;
}

static struct ast *ast_redir_list(void)
{
    struct ast *ast_redir_list = ast_init("redir_list", OPERATOR_REDIR_LIST);
    struct ast *ast_redir_1 = ast_redir_A();
    ast_add_child(ast_redir_list, ast_redir_1);
    
    struct ast *ast_redir_next = ast_init("redir_list", OPERATOR_REDIR_LIST);
    ast_add_child(ast_redir_list, ast_redir_next);
    struct ast *ast_redir_2 = ast_redir_B();

    ast_add_child(ast_redir_next, ast_redir_2);
    return ast_redir_list;
}

struct ast *ast_command_A(void)
{
    struct ast *ast_command = ast_init("cmd", OPERATOR_COMMAND);

    struct ast *arg_list = ast_arg_list();
    struct ast *redir_list = ast_redir_list();

    ast_add_child(ast_command, arg_list);
    ast_add_child(ast_command, redir_list);

    return ast_command;
}

struct ast *ast_command_B(void)
{
    struct ast *ast_command = ast_init("cmd", OPERATOR_COMMAND);

    struct ast *arg_list = ast_arg_list();
    ast_add_child(ast_command, arg_list);

    return ast_command;
}

struct ast *ast_pipe(void)
{
    struct ast *ast_pipe = ast_init("pipe", OPERATOR_PIPE);
    struct ast *command_1 = ast_command_A();
    ast_add_child(ast_pipe, command_1);

    struct ast *ast_pipeline = ast_init("pipeline", OPERATOR_PIPE);
    ast_add_child(ast_pipe, ast_pipeline);
    struct ast *command_2 = ast_command_B();
    ast_add_child(ast_pipeline, command_2);
    return ast_pipe;
}

int main(int argc, char **argv)
{

    struct ast *root = ast_init("root", OPERATOR_AND);
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    if (q == 0)
        ast_add_child(root, ast_pipe());

    ast_dot_print(root, "ast.dot");
    struct execution_bundle bundle;
    printf("%d\n", ast_execute(root, &bundle));
    ast_free(root);
    return 0;
}
