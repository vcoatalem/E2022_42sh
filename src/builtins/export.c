#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

extern char **environ;

int builtin_export(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr)
        return 1;
    //struct execution_bundle *bundle = bundle_ptr;
    if (size == 1 || (size == 2 && strcmp(str[1], "-p") == 0))
    {
        for (char **env = environ; *env; ++env)
            printf("declare -x %s\n", *env);
    }
    else if (size >= 3 && strcmp(str[1], "-n"))
    {
        for (size_t i = 2; i < size; ++i)
        {
            unsetenv(str[i]);
        }
    }
    else if (size > 2)
    {
        for (size_t i = 2; i < size; ++i)
        {
            putenv(str[i]);
        }
    }

    return 0;

}