#ifndef EXECUTION_H
#define EXECUTION_H

#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

// REDIRECTION

#define RETURN_SUCCESS 0
#define RETURN_ERROR -1

enum REDIRECTION_TYPE
{
    REDIRECTION_NONE,
    STDIN_FROM_ARG,   // < arg
    STDOUT_TO_ARG,    // 1> arg
    STDERR_TO_ARG,     // 2> arg
    STDOUT_TO_STDERR, // 1>&2
    STDERR_TO_STDOUT, // 2>&1
};

struct redirection
{
    enum REDIRECTION_TYPE type;
    char *arg;
};

struct redirection *redirection_init(enum REDIRECTION_TYPE type, char *arg);
void redirection_free(struct redirection *redirection);
void redirection_print(struct redirection *redirection);

int redirection_execute(struct redirection *redirection);

// COMMAND

struct command
{
    char **args;
    size_t n_args;
    struct redirection **redirections;
    size_t n_redirections;
};

struct command *command_init(char **args, size_t n_args,
        struct redirection **redirections, size_t n_redirections);
void command_free(struct command *command);
void command_print(struct command *command);

int command_execute(struct command *command);

// PIPE

struct pipe
{
    struct command **commands;
    size_t n_commands;
};

struct pipe *pipe_init(void);
void pipe_command(struct pipe *pipe, struct command *cmd);
void pipe_free(struct pipe *pipe);
void pipe_print(struct pipe *pipe);

int pipe_execute(struct pipe *pipe);

#endif /* EXECUTION_H */
