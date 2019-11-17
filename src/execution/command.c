#include "execution.h"

#if 0

struct command
{
    char **args;
    size_t n_args;
    struct redirection **redirections;
    size_t n_redirections;
    int fd_in;
    int fd_out;
    int fd_err;
    struct command *pipe;
};

#endif

struct command *command_init(char **args, struct redirection **redirections)
{
    struct command *cmd = calloc(1, sizeof(struct command));
    while (*(args + cmd->n_args))
    {
        cmd->n_args++;
    }
    cmd->args = calloc(cmd->n_args + 1, sizeof(void*));
    for (size_t i = 0; i < cmd->n_args; i++)
    {
        *(cmd->args + i) = strdup(*(args + i));
    }

    if (redirections)
    {
        cmd->redirections = redirections;
        while (*(redirections + cmd->n_redirections))
        {
            cmd->n_redirections++;
        }
    }
    return cmd;
}

static void command_free_fd(struct command *command)
{
    if (command->fd_in > 2)
        close(command->fd_in);
    if (command->fd_out > 2)
        close(command->fd_out);
    if (command->fd_err > 2)
        close(command->fd_err);
}

void command_free(struct command *command)
{
    if (!command)
        return;
    for (size_t i = 0; i < command->n_args; i++)
    {
        free(*(command->args + i));
    }
    free(command->args);
    for (size_t i = 0; i < command->n_redirections; i++)
    {
        redirection_free(*(command->redirections + i));
    }
    free(command->redirections);
    free(command);
}


void command_print(struct command *command)
{
    printf("command:");
    for (size_t i = 0; i < command->n_args; i++)
    {
        printf(" %s", *(command->args + i));
    }
    printf (" ||");
    for (size_t i = 0; i < command->n_redirections; i++)
    {
        printf(" | ");
        redirection_print(*(command->redirections + i));
    }
    printf("\n");
}

void command_add_redirection(struct command *command, struct redirection *redir)
{
    command->n_redirections++;
    command->redirections = realloc(command->redirections,
            sizeof(void*) * command->n_redirections + 1);
    *(command->redirections + command->n_redirections - 1) = redir;
    *(command->redirections + command->n_redirections) = NULL;
}

/*
**
** command_execute executes command->next
**
*/

int command_execute(struct command *command)
{
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        ////child
        //apply redirection
        for (size_t i = 0; i < command->n_redirections; i++)
        {
            redirection_execute(command, *(command->redirections + i));
        } 
        //execute command
        execvp(*(command->args), command->args);
        //if execution failed
        command_free_fd(command);
        exit(RETURN_ERROR);
    }
    waitpid(pid, &status, 0);
    //printf("[LOG] command %s received %d\n", *(command->args), status); 
    return status;
}
