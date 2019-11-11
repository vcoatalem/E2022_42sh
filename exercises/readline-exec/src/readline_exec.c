#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include "readline.h"
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void  parse(char *line, char **argv)
{
    char *delimit = " \t\n";
    char *save;
    argv[0] = strtok_r(line, delimit, &save);
    char *token;
    int i = 0;
    while((token = strtok_r(NULL, delimit, &save)) != NULL)
    {
        i++;
        argv[i] = token;
    }
    argv[++i] = '\0';
}



void execcmd(char **cmd)
{
    pid_t pid;
    int stat;

    pid = fork();
    if (pid < 0)
        err(666, "Hudson We have a problem!");
    if (pid == 0)
    {
        execvp(*cmd, cmd);
        exit(0);
    }
    else
        wait(&stat);

}

int main(void)
{
    char *input = NULL;
    char *argv[128];
    while (1)
    {
        input = get_next_line("21sh$ ");
        if (!input)
            break;
        parse(input, argv);
        execcmd(argv);
        free(input);
    }

    return 0;
}
