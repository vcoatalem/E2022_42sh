#include "execution.h"

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
    pipe->commands = realloc(pipe->commands,
            sizeof(void*) * (pipe->n_commands + 2));
    pipe->commands[pipe->n_commands] = command;
    pipe->commands[pipe->n_commands + 1] = NULL;
    pipe->n_commands++;
}

int pipe_execute(struct pipe *p)
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
        //printf("[LOG] command: ");
        /*for (size_t i = 0; i < (*(p->commands + iterator))->n_args; i++)
        {
            printf(" %s", *((*(p->commands + iterator))->args) + i);
        }
        printf("\n");*/
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
                int try_execute =
                        command_execute(*(p->commands + iterator));
                ///**/printf("[LOG] forked command child will return: %d\n", try_execute);
                exit(try_execute % 255);
            }
            else
            {
                waitpid(sub_pid, &sub_status, 0);
                ///**/printf("[LOG] forked command child returned: %d\n", sub_status);
                exit(sub_status % 255);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
            ///**/printf("[LOG] pipe received status: %d\n", status);
            if (status != 0)
            {
                return status % 255;
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
