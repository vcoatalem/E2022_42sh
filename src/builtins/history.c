#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

enum
{
    SUCCESS,
    ERROR_INVALID_FILE,
    ERROR_INVALID_ARGS
};

static int error_fd( char* file)
{
    warn("%s", file);
    return ERROR_INVALID_FILE;
}


static int builtin_historybis(char **str, size_t size, void *bundle_ptr)
{
    char *line = NULL;
    size_t sizeline;
    if (!bundle_ptr)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    char *historyfile = get_variable(bundle->hash_table_var, "HISTFILE");
    if (size == 3 && strcmp(str[1], "-r") == 0)
    {
        FILE* fdhistoy = fopen(historyfile, "a");
        if (!fdhistoy)
            return error_fd(".42sh_history");
        FILE* fdfile = fopen(str[2], "r");
        if (!fdfile)
            return error_fd(str[2]);
        while(getline(&line, &sizeline, fdfile) != -1)
            fputs(line, fdhistoy);
        fclose(fdhistoy);
        fclose(fdfile);
    }
    else
        return ERROR_INVALID_ARGS;
    return SUCCESS;
}


int builtin_history(char **str, size_t size, void *bundle_ptr)
{
    char *line = NULL;
    size_t sizeline;
    if (!bundle_ptr)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    char *historyfile = get_variable(bundle->hash_table_var, "HISTFILE");
    if (size == 1)
    {
        FILE *fd = fopen(historyfile, "r");
        if (!fd)
            return error_fd(".42sh_history");
        while(getline(&line, &sizeline, fd) != -1)
            printf("%s", line);
        fclose(fd);
    }
    else if (strcmp(str[1], "-c") == 0)
    {
        FILE *fd = fopen(historyfile, "w");
        if (!fd)
            return error_fd(".42sh_history");
        fclose(fd);
    }
    else
        return builtin_historybis(str, size, bundle_ptr);
    return SUCCESS;
}
