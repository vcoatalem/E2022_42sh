#include "options.h"
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>

#include <stdio.h>

struct options *options_init(void)
{
    struct options *new_options = malloc(sizeof(struct options));

    if (new_options == NULL)
        return NULL;

    new_options->no_options = 0;
    new_options->command = NULL;
    new_options->norc_is_set = 0;
    new_options->ast_print_is_set = 0;
    new_options->print_shopt_is_set = 0;
    new_options->nb_set_shopt = 0;
    new_options->set_shopt = NULL;
    new_options->nb_unset_shopt = 0;
    new_options->unset_shopt = NULL;
    new_options->script = NULL;

    return new_options;
}

static int is_flag(char *arg)
{
    return *arg == '-' || *arg == '+';
}

static void set_command(struct options *options, int *i, char **argv)
{
    *i = *i + 1;
    while (*(argv + *i) && is_flag(*(argv + *i)))
    {
        *i = *i + 1;
    }
    if (!options->command)
    {
        options->command = *(argv + *i);
    }
}

static void set_set_shopt(struct options *options, int *index, char *argv[])
{
    *index = *index + 1;
    if (argv[*index] != NULL)
    {
        options->nb_set_shopt++;
        options->set_shopt = realloc(options->set_shopt,
                        options->nb_set_shopt * sizeof(char *));
        options->set_shopt[options->nb_set_shopt - 1] = argv[*index];
    }

    else
        options->print_shopt_is_set = 1;
}

static void set_unset_shopt(struct options *options, int *index, char *argv[])
{
    *index = *index + 1;
    if (argv[*index] != NULL)
    {
        options->nb_unset_shopt++;
        options->unset_shopt = realloc(options->unset_shopt,
                            options->nb_unset_shopt * sizeof(char *));

        options->unset_shopt[options->nb_unset_shopt - 1] = argv[*index];
    }

    else
        options->print_shopt_is_set = 1;
}

int get_option_type(struct options *options, int argc, char *argv[])
{
    if (argc == 0)
        options->no_options = 1;

    for (int i = 0; i < argc; i++)
    {
        char *s = argv[i];

        if (!is_flag(s) && options->command == NULL)
        {
            options->script = s;
            break;
        }

        if (strcmp(s, "-c") == 0 && options->script == NULL)
        {
            if (i + 1 < argc)
                set_command(options, &i, argv);

            else
            {
                warn("42sh: -c: option requires an argument");
                return OPTIONS_FAILURE;
            }
        }
        else if (strcmp(s, "--norc") == 0)
            options->norc_is_set = 1;

        else if (strcmp(s, "--ast-print") == 0)
            options->ast_print_is_set = 1;

        else if (strcmp(s, "-O") == 0)
            set_set_shopt(options, &i, argv);

        else if (strcmp(s, "+O") == 0)
            set_unset_shopt(options, &i, argv);

        // TODO: Add cases for options not implemented yet
    }

    return OPTIONS_SUCCESS;
}

void options_free(struct options *options)
{
    free(options->set_shopt);
    free(options->set_shopt);
    free(options);
}

struct options *options_build(int argc, char **argv)
{
    struct options *options = options_init();
    if (argc >= 2)
    {
        int get_options = get_option_type(options, argc - 1, argv + 1);
        if (get_options != OPTIONS_SUCCESS)
        {
            options_free(options);
            return NULL;
        }
    }
    return options;
}
