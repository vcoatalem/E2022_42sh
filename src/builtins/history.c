#include "builtins.h"
#include "../main/42sh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

enum
{
    SUCCESS,
    ERROR_INVALID_FILE
};

static int error_fd( char* file)
{
    warn("No %s file\n", file);
    return ERROR_INVALID_FILE;
}



int builtin_history(char **str, size_t size, void *bundle_ptr)
{
    char *line = NULL;
    size_t sizeline;
    if (!bundle_ptr)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    char *historyfile = get_variable(bundle->hash_table_var, "HISTFILE");
    if (!size)
    {
        FILE *fd = fopen(historyfile, "r");
        if (!fd)
            return error_fd(".42sh_history");
        while(getline(&line, &sizeline, fd) != -1)
            printf("%s\n", line);
        fclose(fd);
    }
    else if (strcmp(str[0], "-c"))
    {
        FILE *fd = fopen(historyfile, "w");
        if (!fd)
            return error_fd(".42sh_history");
        fclose(fd);
    }
    else if (size == 2 && strcmp(str[0], "-r"))
    {
        FILE* fdhistoy = fopen(historyfile, "a");
        if (!fdhistoy)
            return error_fd(".42sh_history");
        FILE* fdfile = fopen(str[1], "r");
        if (!fdfile)
            return error_fd(str[1]);
        while(getline(&line, &sizeline, fdfile) != -1)
            fputs(line, fdhistoy);
        fclose(fdhistoy);
        fclose(fdfile);
    }
    return SUCCESS;
}
