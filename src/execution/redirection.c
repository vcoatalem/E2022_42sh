#include "execution.h"

#if 0
enum REDIRECTION_TYPE
{
    REDIRECTION_NONE,
    STDIN_FROM_ARG,   // < arg
    STDOUT_TO_ARG,    // 1> arg
    STDERR_TO_ARG     // 2> arg
    STDOUT_TO_STDERR, // 1>&2
    STDERR_TO_STDOUT, // 2>&1
};

struct redirection
{
    enum REDIRECTION_TYPE type;
    char *arg;
};
#endif

struct redirection *redirection_init(enum REDIRECTION_TYPE type, char *arg)
{
    struct redirection *res = calloc(1, sizeof(struct redirection));
    res->type = type;
    res->arg = arg;
    return res;
}

void redirection_free(struct redirection *redirection)
{
    free(redirection);
}

void redirection_print(struct redirection *redirection)
{
    printf("Redirection of type %d and arg %s\n",
            redirection->type, redirection->arg);
}

static void redirect(int from, int to)
{
    printf("redirect %d to %d\n", from, to);
    dup2(to, from);
    close(to);
}

int redirection_execute(struct redirection *redirection)
{
    if (redirection->type == STDIN_FROM_ARG)
    {
        int fd = open(redirection->arg, O_RDONLY);
        if (fd == -1)
            return RETURN_ERROR;
        redirect(STDIN_FILENO, fd); 
    }
    else if (redirection->type == STDOUT_TO_ARG
        || redirection->type == STDERR_TO_ARG)
    {
        int fd = open(redirection->arg, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
            return RETURN_ERROR;
        if (redirection->type == STDOUT_TO_ARG)
            redirect(STDOUT_FILENO, fd);
        else
            redirect(STDERR_FILENO, fd);
    }
    else if (redirection->type == STDOUT_TO_STDERR)
    {
        redirect(STDOUT_FILENO, STDERR_FILENO);
    }
    else if (redirection->type == STDERR_TO_STDOUT)
    {
        redirect(STDERR_FILENO, STDOUT_FILENO);
    }
    return RETURN_SUCCESS;
}
