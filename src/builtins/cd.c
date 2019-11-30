#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include "builtins.h"
#include "../main/42sh.h"


int errordir(char *dir)
{
    printf("42sh: cd: %s: no such file or directory", dir);
    return 1;
}

int errortoomuch(void)
{
    printf("42sh: cd: too much args");
    return 1;
}


int builtin_cd(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || strcmp(str[0], "cd") != 0)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        insert_variable(bundle->hash_table_var, "OLDPWD", getcurrent());
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
            printf("%s\n", get_variable(bundle->hash_table_var, "OLDPWD"));
            res = chdir(get_variable(bundle->hash_table_var, "OLDPWD"));
        }
        else
        {
            insert_variable(bundle->hash_table_var, "OLDPWD", getcurrent());
            res = chdir(str[1]);
        }
        if (res == -1)
            return errordir(str[1]);
        /*printf("lastel=%c\n", str[1][strlen(str[1]) - 1]);
        if (str[1][strlen(str[1]) - 1] == '/')
            str[1][strlen(str[1]) - 1] = 0;
        char *newps1 = calloc(1, 2048);
        strcat(newps1, "42sh:");
        strcat(newps1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        strcat(newps1, "$");
        printf("ps1 = %s\n", newps1);
        insert_variable(bundle->hash_table_var, "ps1", newps1);*/
        return 0;
    }
    return errortoomuch();
}
