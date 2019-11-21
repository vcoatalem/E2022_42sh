#include "builtins.h"

enum
{
    SUCCESS,
    ERROR_INVALID_FILE
};

static int error_fd( char* file)
{
    printf("No %s file\n", file);
    return ERROR_INVALID_FILE;
}



int builtin_history(char **str, size_t size,struct execution_bundle *bundle)
{
    char *line = NULL;
    size_t sizeline;
    if (!bundle)
        return 1;
    else if (!size)
    {
        FILE *fd = fopen(".42sh_history", "r");
        if (!fd)
            return error_fd(".42sh_history");
        while(getline(&line, &sizeline, fd) != -1)
            printf("%s\n", line);
        fclose(fd);
    }
    else if (strcmp(str[0], "-c"))
    {
        FILE *fd = fopen(".42sh_history", "w");
        if (!fd)
            return error_fd(".42sh_history");
        fclose(fd);
    }
    else if (size == 2 && strcmp(str[0], "-r"))
    {
        FILE* fdhistoy = fopen(".42sh_history", "a");
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