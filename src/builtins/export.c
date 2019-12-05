#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

static void set_variable_name_value(char *str, char* varname, char *varvalue)
{
    size_t it = 0;
    size_t name_it = 0;
    size_t val_it = 0;
    int parsing_state = 0;
    while (*(str + it))
    {
        if (*(str + it) == '=')
        {
            parsing_state = 1;
        }
        else
        {
            if (parsing_state == 0)
            {
                *(varname + name_it) = *(str + it);
                name_it++;
            }
            else
            {
                *(varvalue + val_it) = *(str + it);
                val_it++;
            }
        }
        it++;
    }
}

extern char **environ;

int builtin_export(char **argv, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr)
        return 1;
    //struct execution_bundle *bundle = bundle_ptr;
    if (size == 1 || (size == 2 && strcmp(argv[1], "-p") == 0))
    {
        for (char **env = environ; *env; ++env)
            printf("declare -x %s\n", *env);
    }
    else if (size >= 3 && strcmp(argv[1], "-n"))
    {
        for (size_t i = 2; i < size; ++i)
        {
            unsetenv(argv[i]);
        }
    }
    else if (size >= 2)
    {
        for (size_t i = 1; i < size; ++i)
        {
            char var_buffer[4096] = { 0 };
            char val_buffer[4096] = { 0 };
            set_variable_name_value(argv[i], var_buffer, val_buffer);
            setenv(var_buffer, val_buffer, 1);
        }
    }

    return 0;

}
