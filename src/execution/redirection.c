#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "execution.h"
#include "../main/42sh.h"

struct redirection *redirection_init(enum REDIRECTION_TYPE type, char *arg)
{
    struct redirection *res = calloc(1, sizeof(struct redirection));
    res->type = type;
    if (arg)
        res->arg = strdup(arg);
    return res;
}

void redirection_free(struct redirection *redirection)
{
    if (!redirection)
        return;
    if (redirection->arg)
        free(redirection->arg);
    free(redirection);
}

static void redirect(int *to_ptr, int to, int from)
{
    *to_ptr = to;
    dup2(to, from);
}

static void redirection_execute_heredoc(struct command *cmd,
        struct redirection *redirection, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    int p[2];
    pipe(p);
    char *limit = redirection->arg;
    char *ps2 = get_variable(bundle->hash_table_var, "PS2");
    char *input = NULL;
    if (redirection->type == HEREDOC_DASH)
    {
        //disable tab stripping
        rl_bind_key('\t', rl_insert);
    }
    while (1)
    {
        input = readline(ps2);
        if (!strcmp(input, limit))
        {
            free(input);
            break;
        }
        if (!input)
            continue;
        write(p[PIPE_WRITE], input, strlen(input));
        write(p[PIPE_WRITE], "\n", 1);
        free(input);
    }
    redirect(&cmd->fd_in, p[PIPE_READ], STDIN_FILENO);
    close(p[PIPE_WRITE]);
}

static int redirection_execute_stdin_from_arg(struct command *cmd,
        struct redirection *redirection)
{
        int fd = open(redirection->arg, O_RDONLY);
        if (fd == -1)
        {
            warnx("could not open file `%s` to read input from",
                    redirection->arg);
            return RETURN_REDIRECTION_ERROR;
        }
        redirect(&cmd->fd_in, fd, STDIN_FILENO);
        return RETURN_SUCCESS;
}

static int redirection_execute_std_to_arg(struct command *cmd,
        struct redirection *redirection)
{
    if (redirection->type == STDOUT_TO_ARG
        || redirection->type == STDERR_TO_ARG)
    {
        int fd = open(redirection->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            warnx("could not open file `%s` to output into",
                    redirection->arg);
            return RETURN_REDIRECTION_ERROR;
        }
        if (redirection->type == STDOUT_TO_ARG)
        {
            redirect(&cmd->fd_out, fd, STDOUT_FILENO);
        }
        else
        {
            redirect(&cmd->fd_err, fd, STDERR_FILENO);
        }
    }
    else if (redirection->type == STDOUT_APPEND_TO_ARG
        || redirection->type == STDERR_APPEND_TO_ARG)
    {
        int fd = open(redirection->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            warnx("could not open file `%s` to concat into",
                    redirection->arg);
            return RETURN_REDIRECTION_ERROR;
        }
        if (redirection->type == STDOUT_APPEND_TO_ARG)
        {
            redirect(&cmd->fd_out, fd, STDOUT_FILENO);
        }
        else
        {
            redirect(&cmd->fd_err, fd, STDERR_FILENO);
        }
    }
    return RETURN_SUCCESS;
}

int redirection_execute(struct command *cmd, struct redirection *redirection,
        void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] applying redirection: type: %d; arg: %s\n",
                redirection->type, redirection->arg ? redirection->arg : "");
    }
    if (redirection->type == STDIN_FROM_ARG)
    {
        redirection_execute_stdin_from_arg(cmd, redirection);
    }
    else if (redirection->type == STDOUT_TO_ARG
        || redirection->type == STDERR_TO_ARG
        || redirection->type == STDOUT_APPEND_TO_ARG
        || redirection->type == STDERR_APPEND_TO_ARG)
    {
        redirection_execute_std_to_arg(cmd, redirection);
    }
    else if (redirection->type == STDOUT_TO_STDERR)
    {
        redirect(&cmd->fd_err, dup(STDOUT_FILENO), STDERR_FILENO);
    }
    else if (redirection->type == STDERR_TO_STDOUT)
    {
        redirect(&cmd->fd_out, dup(STDERR_FILENO), STDOUT_FILENO);
    }
    else if (redirection->type == HEREDOC || redirection->type == HEREDOC_DASH)
    {
        redirection_execute_heredoc(cmd, redirection, bundle_ptr);
    }
    return RETURN_SUCCESS;
}
