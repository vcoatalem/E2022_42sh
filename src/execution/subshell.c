#include <err.h>

#include "execution.h"

#define SUBSHELL_MAX_SIZE 8192


//args: { "42sh", "-c", "[subshell content]", NULL }

char *substitute_shell(char *command)
{
    char *args[] =
    {
        "42sh",
        "-c",
        command,
        NULL
    };
    char *env[] =
    {
        NULL
    };
    int p[2];
    pipe(p);
    pid_t pid = fork();
    int status;
    if (pid == 0)
    {
        dup2(p[PIPE_WRITE], STDOUT_FILENO);
        execve("./42sh", args, env);
        //somthing went wrong..
        warnx("could not initialise subshell...");
        exit (RETURN_UNKNOWN_COMMAND);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    char buffer[SUBSHELL_MAX_SIZE] = { 0 };
    read(p[PIPE_READ], buffer, SUBSHELL_MAX_SIZE - 1);
    return strdup(buffer);
}
