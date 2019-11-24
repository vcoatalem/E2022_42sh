#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../main/42sh.h"
#include "../ast.h"

static struct ast *ast_arg_list_A(void)
{
    struct ast *ast_args = ast_init("arglist1", OPERATOR_ARG_LIST);
    struct ast *ast_next1 = ast_init("arglist2", OPERATOR_ARG_LIST);
    struct ast *ast_next2 = ast_init("arglist3", OPERATOR_ARG_LIST);
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

static struct ast *ast_arg_list_B(void)
{
    struct ast *ast_args = ast_init("args", OPERATOR_ARG_LIST);
    struct ast *arg1 = ast_init("arg1", OPERATOR_GET_VALUE);
    struct ast *arg = ast_init("ls", OPERATOR_NONE);
    ast_add_child(ast_args, arg1);
    ast_add_child(arg1, arg);
    return ast_args;
}

static struct ast *ast_arg_list_C(void)
{

    struct ast *ast_arg_list_1 = ast_init("args", OPERATOR_ARG_LIST);
    struct ast *ast_arg_list_2 = ast_init("args", OPERATOR_ARG_LIST);
    ast_add_child(ast_arg_list_1, ast_arg_list_2);
    struct ast *ast_arg_list_3 = ast_init("args", OPERATOR_ARG_LIST);
    ast_add_child(ast_arg_list_2, ast_arg_list_3);
    struct ast *ast_arg_list_4 = ast_init("args", OPERATOR_ARG_LIST);
    ast_add_child(ast_arg_list_3, ast_arg_list_4);
    struct ast *ast_arg_list_5 = ast_init("args", OPERATOR_ARG_LIST);
    ast_add_child(ast_arg_list_4, ast_arg_list_5);

    struct ast *ast_arg1 = ast_init("[", OPERATOR_GET_VALUE);
    struct ast *ast_arg2 = ast_init("1", OPERATOR_GET_VALUE);
    struct ast *ast_arg3 = ast_init("-eq", OPERATOR_GET_VALUE);
    struct ast *ast_arg4 = ast_init("2", OPERATOR_GET_VALUE);
    struct ast *ast_arg5 = ast_init("[", OPERATOR_GET_VALUE);
    ast_add_child(ast_arg_list_1, ast_arg1);
    ast_add_child(ast_arg_list_2, ast_arg2);
    ast_add_child(ast_arg_list_3, ast_arg3);
    ast_add_child(ast_arg_list_4, ast_arg4);
    ast_add_child(ast_arg_list_5, ast_arg5);

    struct ast *arg1 = ast_init("[", OPERATOR_NONE);
    struct ast *arg2 = ast_init("1", OPERATOR_NONE);
    struct ast *arg3 = ast_init("-eq", OPERATOR_NONE);
    struct ast *arg4 = ast_init("2", OPERATOR_NONE);
    struct ast *arg5 = ast_init("]", OPERATOR_NONE);
    ast_add_child(ast_arg1, arg1);
    ast_add_child(ast_arg2, arg2);
    ast_add_child(ast_arg3, arg3);
    ast_add_child(ast_arg4, arg4);
    ast_add_child(ast_arg5, arg5);

    return ast_arg_list_1;
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
    struct ast *ast_simple_command = ast_init("simple_cmd", OPERATOR_COMMAND);
    ast_add_child(ast_command, ast_simple_command);

    struct ast *arg_list = ast_arg_list_A();
    struct ast *redir_list = ast_redir_list();

    ast_add_child(ast_simple_command, arg_list);
    ast_add_child(ast_simple_command, redir_list);

    return ast_command;
}

struct ast *ast_command_B(void)
{
    struct ast *ast_command = ast_init("cmd", OPERATOR_COMMAND);
    struct ast *ast_simple_command = ast_init("simple_cmd", OPERATOR_COMMAND);
    ast_add_child(ast_command, ast_simple_command);

    struct ast *arg_list = ast_arg_list_A();
    ast_add_child(ast_simple_command, arg_list);

    return ast_command;
}

struct ast *ast_command_C(void)
{
    struct ast *ast_command = ast_init("cmd", OPERATOR_COMMAND);
    struct ast *ast_simple_command = ast_init("simple_cmd", OPERATOR_COMMAND);
    ast_add_child(ast_command, ast_simple_command);

    struct ast *arg_list = ast_arg_list_B();
    ast_add_child(ast_simple_command, arg_list);

    return ast_command;
}

struct ast *ast_command_D(void)
{
    struct ast *ast_command = ast_init("cmd", OPERATOR_COMMAND);
    struct ast *ast_simple_command = ast_init("cmd", OPERATOR_COMMAND);
    ast_add_child(ast_command, ast_simple_command);

    struct ast *arg_list = ast_arg_list_C();
    ast_add_child(ast_simple_command, arg_list);
    return ast_command;
}

struct ast *ast_pipe_A(void)
{
    struct ast *ast_pipe_1 = ast_init("pipe", OPERATOR_PIPE);
    struct ast *ast_pipeline_1 = ast_init("pipeline", OPERATOR_PIPE);
    struct ast *command_1 = ast_command_A();
    ast_add_child(ast_pipe_1, command_1);
    ast_add_child(ast_pipe_1, ast_pipeline_1);

    struct ast *ast_pipe_2 = ast_init("pipe", OPERATOR_PIPE);
    struct ast *command_2 = ast_command_C();
    ast_add_child(ast_pipe_2, command_2);

    ast_add_child(ast_pipeline_1, ast_pipe_2);
    return ast_pipe_1;
}

//contains one command that succeeds
struct ast *ast_pipe_B(void)
{
    struct ast *ast_pipe = ast_init("pipe", OPERATOR_PIPE);
    struct ast *ast_command = ast_command_C();
    ast_add_child(ast_pipe, ast_command);
    return ast_pipe;
}

//contains one command that fails
struct ast *ast_pipe_C(void)
{
    struct ast *ast_pipe = ast_init("pipe", OPERATOR_PIPE);
    struct ast *ast_command = ast_command_D();
    ast_add_child(ast_pipe, ast_command);
    return ast_pipe;
}

struct ast *ast_or(void)
{
    struct ast *ast_or = ast_init("or", OPERATOR_OR);
    struct ast *ast_pipe1 = ast_pipe_B();
    struct ast *ast_pipe2 = ast_pipe_C();
    ast_add_child(ast_or, ast_pipe1);
    ast_add_child(ast_or, ast_pipe2);
    return ast_or;
}

int main(int argc, char **argv)
{

    struct ast *root = ast_init("root", OPERATOR_AND);
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    char *dot_dest = argc < 2 ? "ast.dot" : *(argv + 2);

    int expected_values[] =
    {
        AST_SUCCESS,
        AST_SUCCESS,
        AST_ERROR,
        AST_SUCCESS,
        AST_SUCCESS,
        AST_SUCCESS,
        AST_SUCCESS,
        AST_SUCCESS,
        AST_SUCCESS
    };

    if (q == 0)
    {
        fprintf(stderr, "2 piped sh commands");
        ast_add_child(root, ast_pipe_A());
    }
    if (q == 1)
    {
        fprintf(stderr, "sh command: ls");
        ast_add_child(root, ast_pipe_B());
    }

    if (q == 2)
    {
        fprintf(stderr, "sh `[` that should fail");
        ast_add_child(root, ast_pipe_C());
    }

    if (q == 3)
    {
        fprintf(stderr, "0 or'ed commands");
        ast_add_child(root, ast_or());
    }

    ast_dot_print(root, dot_dest);
    struct execution_bundle bundle;
    bundle.hash_table_var = init_hash_table_var(50);
    bundle.hash_table_func = init_hash_table_func(50);
    int return_value = ast_execute(root, &bundle) == 0 ? AST_SUCCESS : AST_ERROR;
    return_value = return_value == expected_values[q] ? 0 : 1;
    ast_free(root);
    return return_value;
}
