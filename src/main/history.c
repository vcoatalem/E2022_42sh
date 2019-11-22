#include "42sh.h"
#include <readline/history.h>

void init_history(void)
{
    FILE *fd = fopen(".42sh_history", "r");
    if (!fd)
        fd = fopen(".42sh_history", "w");
    if (!fd)
    {
        return;
    }
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, fd) != -1)
    {
        line[strlen(line) - 1] = '\0';
        add_history(line);
    }
    free(line);
}


void appendhistory(char *cmd)
{
    FILE *fd = fopen(".42sh_history", "at");
    if (!fd)
        fd = fopen(".42sh_history", "wt");
    if (!fd)
    {
        return;
    }
    add_history(cmd);
    fputs(cmd, fd);
    fputs("\n", fd);

    fclose(fd);
}