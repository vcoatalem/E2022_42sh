#include "builtins.h"
#include "../main/42sh.h"
#include "../options/options.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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
    struct shopt *res = malloc(sizeof(struct shopt));
    shopt_init_set_shopt(res, 0, options->unset_shopt,
            options->nb_unset_shopt);
    shopt_init_set_shopt(res, 0, options->set_shopt, options->nb_set_shopt);
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
    return -1;
}

void shopt_print_option(struct shopt *shopt, char **option_array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (shopt_is_set(shopt, option_array[i]))
            printf("%s \t on\n", option_array[i]);
        else
            printf("%s \t off\n", option_array[i]);
    }
}
int builtin_shopt(char **args, size_t size, void *bundle_ptr)
{
    //linit a deja eu lieu auparavant. cherche bundle->shopt et execute dessus
    struct execution_bundle *bundle = bundle_ptr;
    if (!strcmp(args[1], "-s"))
    {
        if (size == 2)
        {
            shopt_print_option(bundle->shopt, bundle->options->unset_shopt,
                    bundle->options->nb_set_shopt);
        }
        else if (!strcmp(args[2], "-q"))
        {
            for (size_t i = 3; i < size; i++)
                shopt_set_option(bundle->shopt, args[i]);
        }
        else
        {
            for (size_t i = 2; i < size; i++)
                shopt_set_option(bundle->shopt, args[i]);
        }
        return 0;
    }
    if (!strcmp(args[1], "-u"))
    {
        if (size == 2)
        {
            shopt_print_option(bundle->shopt, bundle->options->unset_shopt,
                    bundle->options->nb_unset_shopt);
        }
        else if (!strcmp(args[2], "-q"))
        {
            for (size_t i = 3; i < size; i++)
                shopt_unset_option(bundle->shopt, args[i]);
            return 1;
        }
        else
        {
            for (size_t i = 2; i < size; i++)
                shopt_unset_option(bundle->shopt, args[i]);
        }
        return 0;
    }
    if (!strcmp(args[1],"-q"))
    {
        if (size == 2)
            return 0;
        else if (!strcmp(args[2], "-u") || !strcmp(args[2], "-s"))
        {
            if (!strcmp(args[2], "-u"))
            {
                for (size_t i = 3; i < size; i++)
                {
                    shopt_unset_option(bundle->shopt, args[i]);
                }
                return 1;
            }
            else
            {
                for (size_t i = 3; i < size; i++)
                    shopt_set_option(bundle->shopt, args[i]);
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
    shopt_print_option(bundle->shopt, bundle->options->set_shopt,
            bundle->options->nb_set_shopt);
    shopt_print_option(bundle->shopt, bundle->options->unset_shopt,
            bundle->options->nb_unset_shopt);
    return 0;
}
