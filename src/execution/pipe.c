#include "execution.h"

#if 0

struct pipe
{
    struct command **commands;
    size_t n_commands;
};

#endif

struct pipe *pipe_init(void);
void pipe_command(struct pipe *pipe, struct command *cmd);
void pipe_free(struct pipe *pipe);
void pipe_print(struct pipe *pipe);

int pipe_execute(struct pipe *pipe);
