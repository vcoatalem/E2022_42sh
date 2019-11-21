#include "builtins.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

struct shopt
{
    int ast_print;
    int dotglob;
    int expand_aliases;
    int extglob;
    int nocaseglob;
    int nullglob;
    int sourcepath;
    int xpg_echo;
};


void shopt_set_option(struct shopt *shopt, char *str)
{

    if (strcmp(str, "ast_print") == 0)
        shopt->ast_print = 1;
    if (strcmp(str, "dotglob") == 0)
        shopt->dotglob = 1;
    if (strcmp(str, "expand_aliases") == 0)
        shopt->expand_aliases = 1;
    if (strcmp(str, "extglob") == 0)
        shopt->extglob = 1;
    if (strcmp(str, "nocaseglob") == 0)
        shopt->nocaseglob = 1;
    if (strcmp(str, "nullglob") == 0)
        shopt->nullglob = 1;
    if (strcmp(str, "sourcepath") == 0)
        shopt->sourcepath = 1;
    if (strcmp(str, "xpg_echo") == 0)
        shopt->xpg_echo = 1;
}

void shopt_unset_option(struct shopt *shopt, char *str)
{

    if (strcmp(str, "ast_print") == 0)
        shopt->ast_print = 0;
    if (strcmp(str, "dotglob") == 0)
        shopt->dotglob = 0;
    if (strcmp(str, "expand_aliases") == 0)
        shopt->expand_aliases = 0;
    if (strcmp(str, "extglob") == 0)
        shopt->extglob = 0;
    if (strcmp(str, "nocaseglob") == 0)
        shopt->nocaseglob = 0;
    if (strcmp(str, "nullglob") == 0)
        shopt->nullglob = 0;
    if (strcmp(str, "sourcepath") == 0)
        shopt->sourcepath = 0;
    if (strcmp(str, "xpg_echo") == 0)
        shopt->xpg_echo = 0;
}

void shopt_init_set_shopt(struct shopt *shopt, int val,
        char **set_array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(set[i], "ast_print") == 0)
            shopt->ast_print = val;
        if (strcmp(set[i], "dotglob") == 0)
            shopt->dotglob = val;
        if (strcmp(set[i], "expand_aliases") == 0)
            shopt->expand_aliases = val;
        if (strcmp(set[i], "extglob") == 0)
            shopt->extglob = val;
        if (strcmp(set[i], "nocaseglob") == 0)
            shopt->nocaseglob = val;
        if (strcmp(set[i], "nullglob") == 0)
            shopt->nullglob = val;
        if (strcmp(set[i], "sourcepath") == 0)
            shopt->sourcepath = val;
        if (strcmp(set[i], "xpg_echo") == 0)
            shopt->xpg_echo = val;
    }
}

struct shopt shopt_init(struct option *option)
{
    struct shopt *res = malloc(sizeof(*res));
    if (!res)
        return NULL;
    shopt_init_set_shopt(res, 0, option->unset_shopt, option->nb_unset_shopt);
    shopt_init_set_shopt(res, 0, option->set_shopt, option->nb_set_shopt);
    return res;
}

void shopt_free(struct shopt *shopt)
{
    if (!shopt)
        return;
    free(shopt);
}

int shopt_is_set(struct shopt *shopt, char *str)
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
}

void shopt_print_option(struct shopt *shopt, char **option_array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (shopt_is_set(shopt, option_array[i]))
            printf("%s \t on\n", option_array[i]);
        else
            printf("%s \t off\n", option_array[i])
    }
}
int builtin_shopt(char **str, size_t size, struct execution_bundle *bundle)
{
    struct shopt *shopt = shopt_init(bundle->option);
    if (!strcmp(str[1], "-s"))
    {
        if (size == 2)
        {
            shopt_print_option(shopt, bundle->option->unset_shopt,
                    bundle->option->nb_set_shopt);
        }
        else if (!strcmp(str[2], "-q"))
        {
            for (size_t i = 3; i < size; i++)
                set_option(shopt, str[i]);
        }
        else
        {
            for (size_t i = 2; i < size; i++)
                set_option(shopt, str[i]);
        }
        return 0;
    }
    if (!strcmp(str[1], "-u"))
    {
        if (size == 2)
        {
            shopt_print_option(shopt, bundle->option->unset_shopt,
                    bundle->option->nb_unset_shopt);
        }
        else if (!strcmp(str[2], "-q"))
        {
            for (size_t i = 3; i < size; i++)
                unset_option(shopt, str[i]);
            return 1;
        }
        else
        {
            for (size_t i = 2; i < size; i++)
                unset_option(shopt, str[i]);
        }
        return 0;
    }
    if (!strcmp(str[1],"-q"))
    {
        if (size == 2)
            return 0;
        else if (!strcmp(str[2], "-u") || !strcmp(str[2], "-s"))
        {
            if (!strcmp(str[2], "-u"))
            {
                for (size_t i = 3; i < size; i++)
                {
                    unset_option(shopt, str[i]);
                }
                return 1;
            }
            else
            {
                for (size_t i = 3; i < size; i++)
                    set_option(shopt, str[i]);
            }
        }
        else
        {
            int res = 0;
            for (size_t i = 2; i < size; i++)
            {
                if (!shopt_is_set(shopt, str[i]))
                    res = 1;
            }
            return res;
        }
    }
    shopt_print_option(shopt, bundle->option->set_shopt,
            bundle->option->nb_set_shopt);
    shopt_print_option(shopt, bundle->option->unset_shopt,
            bundle->option->nb_unset_shopt);
    return 0;
}
