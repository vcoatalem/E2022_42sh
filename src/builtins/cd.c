#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include "builtins.h"
#include "../main/42sh.h"


static int errordir(char *dir)
{
    warnx("cd: %s: no such file or directory", dir);
    return 1;
}

static int errortoomuch(void)
{
    warnx("cd: too much args");
    return 1;
}

static int erroroldnotset(void)
{
    warnx("cd: OLDPWD not set");
    return 1;
}


int builtin_cd(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || strcmp(str[0], "cd") != 0)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        char *currdir = getcurrent();
        insert_variable(bundle->hash_table_var, "OLDPWD", currdir);
        free(currdir);
        char *home = get_variable(bundle->hash_table_var, "HOME");
        int res = chdir(home);
        if (res == -1)
            return errordir(home);
        return 0;
    }
    if (size == 2)
    {
        int res;
        if (strcmp(str[1], "-") == 0)
        {
            char *old = get_variable(bundle->hash_table_var, "OLDPWD");
            if (!strcmp(old, ""))
            {
                return erroroldnotset();
            }
            printf("%s\n", old);
            res = chdir(old);
        }
        else
        {
            char *currdir = getcurrent();
            insert_variable(bundle->hash_table_var, "OLDPWD", currdir);
            free(currdir);
            res = chdir(str[1]);
        }
        if (res == -1)
            return errordir(str[1]);
        return 0;
    }
    return errortoomuch();
}
