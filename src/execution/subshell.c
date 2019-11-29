#include <err.h>

#include "execution.h"

// echo $(seq 0 1 10)
// -> args= { exec, ./42sh, -c, "seq 0 1 10", NULL }

char *substitute_shell(char **args)
{
    int p[2];
    pipe(p);
    pid_t pid = fork();
    int status;
    if (pid == 0)
    {
        //dup2(p[PIPE_WRITE], STDOUT_FILENO);
        //char *env[] = { NULL };
        
        printf("yoooo %s\n", *args);
        //execve("./42sh", args, env);
        //somthing went wrong..
        exit (RETURN_UNKNOWN_COMMAND);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    char buffer[8092] = { 0 };
    size_t buffer_iterator = 0;
    while (read(p[PIPE_READ], buffer + buffer_iterator, 1))
    {
        warnx("read");
        buffer_iterator++;
    }
    return strdup(buffer);
}
