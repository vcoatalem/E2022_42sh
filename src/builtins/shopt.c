#include "builtins.h"
#include "../main/42sh.h"
#include "../options/options.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>

int shopt_set_option(struct shopt *shopt, char *str)
{
    if (strcmp(str, "ast_print") == 0)
        shopt->ast_print = 1;
    else if (strcmp(str, "dotglob") == 0)
        shopt->dotglob = 1;
    else if (strcmp(str, "expand_aliases") == 0)
        shopt->expand_aliases = 1;
    else if (strcmp(str, "extglob") == 0)
        shopt->extglob = 1;
    else if (strcmp(str, "nocaseglob") == 0)
        shopt->nocaseglob = 1;
    else if (strcmp(str, "nullglob") == 0)
        shopt->nullglob = 1;
    else if (strcmp(str, "sourcepath") == 0)
        shopt->sourcepath = 1;
    else if (strcmp(str, "xpg_echo") == 0)
        shopt->xpg_echo = 1;
    else
    {
        warn("%s is not in 42sh option\n", str);
        return 0;
    }
    return 1;
}

int shopt_unset_option(struct shopt *shopt, char *str)
{

    if (strcmp(str, "ast_print") == 0)
        shopt->ast_print = 0;
    else if (strcmp(str, "dotglob") == 0)
        shopt->dotglob = 0;
    else if (strcmp(str, "expand_aliases") == 0)
        shopt->expand_aliases = 0;
    else if (strcmp(str, "extglob") == 0)
        shopt->extglob = 0;
    else if (strcmp(str, "nocaseglob") == 0)
        shopt->nocaseglob = 0;
    else if (strcmp(str, "nullglob") == 0)
        shopt->nullglob = 0;
    else if (strcmp(str, "sourcepath") == 0)
        shopt->sourcepath = 0;
    else if (strcmp(str, "xpg_echo") == 0)
        shopt->xpg_echo = 0;
    else
    {
        warn("%s is not in 42sh option\n", str);
        return 0;
    }
    return 1;
}

void shopt_init_set_shopt(struct shopt *shopt, int val,
        char **set_array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(set_array[i], "ast_print") == 0)
            shopt->ast_print = val;
        if (strcmp(set_array[i], "dotglob") == 0)
            shopt->dotglob = val;
        if (strcmp(set_array[i], "expand_aliases") == 0)
            shopt->expand_aliases = val;
        if (strcmp(set_array[i], "extglob") == 0)
            shopt->extglob = val;
        if (strcmp(set_array[i], "nocaseglob") == 0)
            shopt->nocaseglob = val;
        if (strcmp(set_array[i], "nullglob") == 0)
            shopt->nullglob = val;
        if (strcmp(set_array[i], "sourcepath") == 0)
            shopt->sourcepath = val;
        if (strcmp(set_array[i], "xpg_echo") == 0)
            shopt->xpg_echo = val;
    }
}

struct shopt *shopt_init(void *options_ptr)
{
    struct options *options = options_ptr;
    struct shopt *res = calloc(1, sizeof(struct shopt));

    //TODO: setup default values for shopt here

    if (options)
    {
        shopt_init_set_shopt(res, 0, options->unset_shopt,
                options->nb_unset_shopt);
        shopt_init_set_shopt(res, 0, options->set_shopt,
                options->nb_set_shopt);
    }
    return res;
}

void shopt_free(struct shopt *shopt)
{
    if (!shopt)
        return;
    free(shopt);
}

static int shopt_is_set(struct shopt *shopt, char *str)
{
    if (strcmp(str, "ast_print") == 0)
        return shopt->ast_print;
    if (strcmp(str, "dotglob") == 0)
        return shopt->dotglob;
    if (strcmp(str, "expand_aliases") == 0)
        return shopt->expand_aliases;
    if (strcmp(str, "extglob") == 0)
        return shopt->extglob;
    if (strcmp(str, "nocaseglob") == 0)
        return shopt->nocaseglob;
    if (strcmp(str, "nullglob") == 0)
        return shopt->nullglob;
    if (strcmp(str, "sourcepath") == 0)
        return shopt->sourcepath;
    if (strcmp(str, "xpg_echo") == 0)
        return shopt->xpg_echo;
    return -1;
}

void shopt_print(struct shopt *shopt, int mode)
{
    if (shopt->ast_print == mode || mode == -1)
        printf("ast_print %s\n", shopt->ast_print ? "on" : "off");
    if (shopt->dotglob == mode || mode == -1)
        printf("dotglob %s\n", shopt->dotglob ? "on" : "off");
    if (shopt->expand_aliases == mode || mode == -1)
        printf("expand_aliases %s\n", shopt->expand_aliases ? "on" : "off");
    if (shopt->extglob == mode || mode == -1)
        printf("extglob %s\n", shopt->extglob ? "on" : "off");
    if (shopt->nullglob == mode || mode == -1)
        printf("nullglob %s\n", shopt->nullglob ? "on" : "off");
    if (shopt->sourcepath == mode || mode == -1)
        printf("sourcepath %s\n", shopt->sourcepath ? "on" : "off");
    if (shopt->xpg_echo == mode || mode == -1)
        printf("xpg_echo %s\n", shopt->xpg_echo ? "on" : "off");
}


static int shopt_s(char **args, size_t size, struct execution_bundle *bundle)
{
    if (size == 2)
        shopt_print(bundle->shopt, 1);
    else if (!strcmp(args[2], "-q"))
    {
        int res = 1;
        for (size_t i = 3; i < size; i++)
        {
            res = shopt_set_option(bundle->shopt, args[i]);
            if (res == 0)
                return 1;
        }
    }
    else
    {
        int res = 1;
        for (size_t i = 2; i < size; i++)
        {
            res = shopt_set_option(bundle->shopt, args[i]);
            if (res == 0)
                return 1;
        }
    }
    return 0;
}


static int shopt_u(char **args, size_t size, struct execution_bundle *bundle)
{
    if (size == 2)
    {
        shopt_print(bundle->shopt, 0);
    }
    else if (!strcmp(args[2], "-q"))
    {
        int res = 1;
        for (size_t i = 3; i < size; i++)
        {
            res = shopt_unset_option(bundle->shopt, args[i]);
            if (res == 0)
                return 1;
        }
        return 1;
    }
    else
    {
        int res = 1;
        for (size_t i = 2; i < size; i++)
        {
            res = shopt_unset_option(bundle->shopt, args[i]);
            if (res == 0)
                return 1;
        }
    }
    return 0;
}

static int shopt_q(char **args, size_t size, struct execution_bundle *bundle)
{
    int check = 1;
    if (size == 2)
        return 0;
    else if (!strcmp(args[2], "-u") || !strcmp(args[2], "-s"))
    {
        if (!strcmp(args[2], "-u"))
        {
            for (size_t i = 3; i < size; i++)
            {
                check = shopt_unset_option(bundle->shopt, args[i]);
                if (check == 0)
                    return 1;
            }
            return 1;
        }
        else
        {
            for (size_t i = 3; i < size; i++)
            {
                check = shopt_set_option(bundle->shopt, args[i]);
                if (check == 0)
                    return 1;
            }
            return 0;
        }
    }
    else
    {
        int res = 0;
        for (size_t i = 2; i < size; i++)
        {
            if (!shopt_is_set(bundle->shopt, args[i]))
                res = 1;
        }
        return res;
    }
}

int builtin_shopt(char **args, size_t size, void *bundle_ptr)
{
    //linit a deja eu lieu auparavant. cherche bundle->shopt et execute dessus
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
        shopt_print(bundle->shopt, -1);
    else if (!strcmp(args[1], "-s"))
        return shopt_s(args, size, bundle);
    else if (!strcmp(args[1], "-u"))
        return shopt_u(args, size, bundle);
    else if (!strcmp(args[1],"-q"))
        return shopt_q(args, size, bundle);
    return 0;
}
