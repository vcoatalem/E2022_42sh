#include "42sh.h"
#include <readline/history.h>

void init_history(struct execution_bundle *bundle)
{
    char *historyfile = get_variable(bundle->hash_table_var, "HISTFILE");
    FILE *fd = fopen(historyfile, "r");
    if (!fd)
        fd = fopen(historyfile, "w");
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


void appendhistory(char *cmd, struct execution_bundle *bundle)
{
    char *historyfile = get_variable(bundle->hash_table_var, "HISTFILE");
    FILE *fd = fopen(historyfile, "at");
    if (!fd)
        fd = fopen(historyfile, "wt");
    if (!fd)
    {
        return;
    }
    add_history(cmd);
    fputs(cmd, fd);
    fputs("\n", fd);

    fclose(fd);
}