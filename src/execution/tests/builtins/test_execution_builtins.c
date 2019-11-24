#include "../../execution.h"
#include "../../../main/42sh.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int q = argc > 1 ? atoi(*(argv + 1)) : 0;
    printf("[LOG] TEST: #%d\n", q);
    
    struct execution_bundle bundle;
    bundle.shopt = shopt_init(NULL);
    bundle.hash_table_func = init_hash_table_func(50);
    bundle.hash_table_var = init_hash_table_var(50);

    struct pipe *p = pipe_init();

    char *shopt[] = { "shopt", NULL };
    char *shopt_s[] = { "shopt", "-s", NULL };
    char *shopt_u[] = { "shopt", "-u", NULL };
    char *shopt_set_arg_incorrect[] = { "shopt", "-u", "im in file", NULL };
    char *shopt_set_arg[] = { "shopt", "-s", "dotglob", NULL };

    char *cat[] = { "cat", NULL };
    char *grep[] = { "grep", "off" };

    char **commands[] =
    {
        cat,                            //0
        shopt,                          //1
        shopt_s,                        //2
        shopt_set_arg_incorrect,        //3
        shopt_set_arg,                  //4
        grep,                           //5
        shopt_u                         //6
    };

    struct redirection *redirect_output = redirection_init(STDOUT_TO_ARG, "output");
    struct redirection *redirect_err = redirection_init(STDERR_TO_ARG, "output");
    struct redirection *redirect_input = redirection_init(STDIN_FROM_ARG, "input");
    struct redirection *redirect_output_to_stderr = redirection_init(STDOUT_TO_STDERR, NULL);
    struct redirection *redirect_stderr_to_output = redirection_init(STDERR_TO_STDOUT, NULL);

    if (q == 0)
    {
        struct command *command = command_init(commands[1], &bundle);
        pipe_add_command(p, command);
    }
    else if (q == 1)
    {
        struct command *command = command_init(commands[2], &bundle);
        pipe_add_command(p, command);
    }
    else if (q == 2)
    {
        struct command *command = command_init(commands[3], &bundle);
        command_add_redirection(command, redirection_dup(redirect_output));
        pipe_add_command(p, command);
    }
    else if (q == 3)
    {
        struct command *command = command_init(commands[4], &bundle);
        command_add_redirection(command, redirection_dup(redirect_input));
        pipe_add_command(p, command);
    }
    else if (q == 4)
    {
        struct command *c1 = command_init(commands[1], &bundle);
        struct command *c2 = command_init(commands[0], &bundle);
        pipe_add_command(p, c1);
        pipe_add_command(p, c2);
    }
    else if (q == 5)
    {
        struct command *c1 = command_init(commands[5], &bundle);
        struct command *c2 = command_init(commands[4], &bundle);
        pipe_add_command(p, c2);
        pipe_add_command(p, c1);
    }
    int return_value = pipe_execute(p, &bundle);

    pipe_free(p);

    redirection_free(redirect_output);
    redirection_free(redirect_err);
    redirection_free(redirect_input);
    redirection_free(redirect_output_to_stderr);
    redirection_free(redirect_stderr_to_output);
    printf("[LOG] test return value: %d\n", return_value);
    return return_value;
}
