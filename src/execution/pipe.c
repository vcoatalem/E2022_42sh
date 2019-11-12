#include "execution.h"

#if 0
struct pipe
{
    struct command **commands;
    size_t n_commands;
}
#endif

#define PIPE_IN 0
#define PIPE_OUT 1

struct pipe *pipe_init(void)
{
    struct pipe *pipe = calloc(1, sizeof(struct pipe));
    pipe->commands = NULL;
    pipe->n_commands = 0;
    return pipe;
}

void pipe_add_command(struct pipe *pipe, struct command *command)
{
    pipe->n_commands++;
    pipe->commands = realloc(pipe->commands,
            sizeof(void*) * pipe->n_commands + 1);
    *(pipe->commands + pipe->n_commands - 1) = command;
    *(pipe->commands + pipe->n_commands - 0) = NULL;
}

unsigned char pipe_execute(struct pipe *p)
{
    if (!p || !p->commands)
        return RETURN_SUCCESS;
    int fd_in = 0;
    int pipe_buffer[2];
    pid_t pid;
    size_t iterator = 0;
    int status = 0;
    while (*(p->commands + iterator))
    {
        pipe(pipe_buffer);
        pid = fork();
        if (pid == 0)
        {
            dup2(fd_in, STDIN_FILENO);
            if (iterator + 1 < p->n_commands)
                dup2(pipe_buffer[PIPE_OUT], STDOUT_FILENO);
            close(pipe_buffer[PIPE_IN]);
            
            pid_t sub_pid = fork();
            int sub_status = 0;
            if (sub_pid == 0)
            {
                unsigned char try_execute =
                        command_execute(*(p->commands + iterator));
                printf("[LOG] forked command will return: %d\n", try_execute);
                exit(try_execute);
            }
            else
            {
                waitpid(sub_pid, &sub_status, 0);
                exit(status);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
            printf("[LOG] pipe received status: %d\n", status);
            if (status != 0)
            {
                return status;
            }
            close(pipe_buffer[PIPE_OUT]);
            fd_in = pipe_buffer[PIPE_IN];
            iterator++;
        }
    }
    return 0;
}

void pipe_free(struct pipe *p)
{
    for (size_t i = 0; i < p->n_commands; i++)
    {
        command_free(*(p->commands + i));
    }
    if (p->commands)
        free(p->commands);
    free(p);
}
