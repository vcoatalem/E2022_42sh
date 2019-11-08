#include "execution.h"

#if 0

struct command
{
    char **args;
    size_t n_args;
    struct redirection **redirections;
    size_t n_redirections;
};

#endif

struct command *command_init(char **args, size_t n_args,
        struct redirection **redirections, size_t n_redirections);
void command_free(struct command *command);
void command_print(struct command *command);

int command_execute(struct command *command);
