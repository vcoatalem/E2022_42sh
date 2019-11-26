#ifndef EXECUTION_H
#define EXECUTION_H

#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

// REDIRECTION
#define RETURN_SUCCESS 0
#define RETURN_ERROR -1

enum REDIRECTION_TYPE
{
    REDIRECTION_NONE = 0,
    STDIN_FROM_ARG   = 11,      // < arg
    STDOUT_TO_ARG    = 21,      // 1> arg
    STDERR_TO_ARG    = 22,      // 2> arg
    STDERR_TO_STDOUT = 31,      // 2>&1
    STDOUT_TO_STDERR = 32,      // 1>&2
    STDOUT_APPEND_TO_ARG = 41,  // 1>> arg
    STDERR_APPEND_TO_ARG = 42,  // 2>> arg
    HEREDOC              = 50,  // <<
    HEREDOC_DASH         = 60,  // <<-
};

struct redirection
{
    enum REDIRECTION_TYPE type;
    char *arg;
};

struct redirection *redirection_init(enum REDIRECTION_TYPE type, char *arg);
void redirection_free(struct redirection *redirection);
void redirection_print(struct redirection *redirection);
struct redirection *redirection_dup(struct redirection *redirection);

// COMMAND

enum command_type
{
    COMMAND_NONE,
    COMMAND_SH,
    COMMAND_BUILTIN,
    COMMAND_FUNCDEC,
    COMMAND_AST
};

struct command
{
    enum command_type type;
    //commands have either a NULL terminated argv or an ast to execute
    int invert_value;
    //
    char **args;
    size_t n_args;
    struct ast *ast;

    struct redirection **redirections;
    size_t n_redirections;
    int save_in;
    int save_out;
    int save_err;
    int fd_in;
    int fd_out;
    int fd_err;
};

struct command *command_init(char **args, void *bundle_ptr);
struct command *shell_command_init(struct ast *ast);
void command_free(struct command *command);
void command_print(struct command *command);
void command_add_redirection(struct command *command,
        struct redirection *redir);

int command_execute(struct command *command, void *bundle_ptr);

void command_apply_redirections(struct command *command, void *bundle_ptr);
void command_restore_flux(struct command *command);

int redirection_execute(struct command *command,
        struct redirection *redirection, void *bundle_ptr);

//PIPE

struct pipe
{
    struct command **commands;
    size_t n_commands;
};

struct pipe *pipe_init(void);
void pipe_add_command(struct pipe *pipe, struct command *command);
int pipe_execute(struct pipe *pipe, void *execution_bundle);
void pipe_free(struct pipe *p);

#endif /* EXECUTION_H */
