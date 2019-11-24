#include <err.h>
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

void redirection_print(struct redirection *redirection)
{
    printf("Redirection of type %d and arg %s\n",
            redirection->type, redirection->arg);
}

struct redirection *redirection_dup(struct redirection *redirection)
{
    return redirection_init(redirection->type, redirection->arg);
}

static void redirect(int from, int to)
{
    //printf("[COMMAND_EXECUTION] redirect %d to %d\n", from, to);
    dup2(to, from);
}

static int redirection_execute_std_to_arg(struct command *cmd,
        struct redirection *redirection)
{
    if (redirection->type == STDOUT_TO_ARG
        || redirection->type == STDERR_TO_ARG)
    {
        int fd = open(redirection->arg, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
            return RETURN_ERROR;
        if (redirection->type == STDOUT_TO_ARG)
        {
            redirect(STDOUT_FILENO, fd);
            cmd->fd_out = fd;
        }
        else
        {
            redirect(STDERR_FILENO, fd);
            cmd->fd_err = fd;
        }
    }
    else if (redirection->type == STDOUT_APPEND_TO_ARG
        || redirection->type == STDERR_APPEND_TO_ARG)
    {
        int fd = open(redirection->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return RETURN_ERROR;
        if (redirection->type == STDOUT_APPEND_TO_ARG)
        {
            redirect(STDOUT_FILENO, fd);
            cmd->fd_out = fd;
        }
        else
        {
            redirect(STDERR_FILENO, fd);
            cmd->fd_err = fd;
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
        int fd = open(redirection->arg, O_RDONLY);
        if (fd == -1)
            return RETURN_ERROR;
        redirect(STDIN_FILENO, fd);
        cmd->fd_in = fd;
    }
    else if (redirection->type == STDOUT_TO_ARG
        || redirection->type == STDERR_TO_ARG
        || redirection->type == STDOUT_APPEND_TO_ARG
        || redirection->type == STDERR_APPEND_TO_ARG)
    {
        int try_redirect = redirection_execute_std_to_arg(cmd, redirection);
        if (try_redirect == RETURN_ERROR)
            warnx("could not open `%s` for redirection", redirection->arg);
    }
    else if (redirection->type == STDOUT_TO_STDERR)
    {
        redirect(STDOUT_FILENO, STDERR_FILENO);
        cmd->fd_out = STDERR_FILENO;
    }
    else if (redirection->type == STDERR_TO_STDOUT)
    {
        redirect(STDERR_FILENO, STDOUT_FILENO);
        cmd->fd_err = STDOUT_FILENO;
    }
    return RETURN_SUCCESS;
}
