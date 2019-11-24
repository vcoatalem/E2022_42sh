#include <stdio.h>
#include <stdlib.h>

#include "../../main/42sh.h"
#include "../builtins.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    char *argv1[] =
    {
        "shopt", NULL
    };
    char *argv2[] =
    {
        "shopt", "-s", NULL
    };
    char *argv3[] =
    {
        "shopt", "-u", NULL
    };
    char *argv4[] =
    {
        "shopt", "-s", "dotglob", NULL
    };
    char *argv5[] =
    {
        "shopt", "-s", "dotglob", "extglob", "nullglob", NULL
    };
    char *argv6[] =
    {
        "shopt", "-u", "dotglob", "nullglob", NULL
    };

    char **args[] =
    {
        argv1,
        argv2,
        argv3,
        argv4,
        argv5,
        argv6,
        NULL
        //...
    };
    int return_value = 0;
    struct options *opt = options_init();
    struct execution_bundle bundle = { 0 };
    bundle.options = opt;
    bundle.shopt = shopt_init(opt);
    if (q == 0)
    {
        //traitements sur loption ici
        return_value = builtin_shopt(args[q], 1, &bundle);
    }
    else if (q == 1)
    {
        return_value = builtin_shopt(args[4], 5, &bundle);
        return_value = builtin_shopt(args[q], 2, &bundle);
    }
    else if (q == 2)
{
        return_value = builtin_shopt(args[q], 2, &bundle);
    }
    else if (q == 3)
    {
        return_value = builtin_shopt(args[q], 3, &bundle);
        shopt_print(bundle.shopt, -1);
    }
    else if (q == 4)
    {
        return_value = builtin_shopt(args[q], 5, &bundle);
        shopt_print(bundle.shopt, -1);
    }
    else if (q == 5)
    {
        return_value = builtin_shopt(args[4], 5, &bundle);
        return_value = builtin_shopt(args[q], 4, &bundle);
        shopt_print(bundle.shopt, -1);
    }/*
    else if (q == 6)
    {
        return_value = builtin_shopt(args[q], 1, &bundle);
    }
    else if (q == 7)
    {
        return_value = builtin_shopt(args[q], 1, &bundle);
    }*/
    shopt_free(bundle.shopt);
    options_free(opt);
    return return_value;
}
