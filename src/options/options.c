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
        err(errno, "ERROR_OPTIONS_INIT: Cannot allocate memory.");

    new_options->no_options = 0;

    new_options->command = NULL;

    new_options->norc_is_set = 0;

    new_options->ast_print_is_set = 0;

    new_options->nb_set_shopt = 0;
    new_options->set_shopt = NULL;

    new_options->nb_unset_shopt = 0;
    new_options->unset_shopt = NULL;

    return new_options;
}

static void set_command(struct options *options, char *arg)
{
    if (!options->command)
    {
        options->command = arg;
    }
}

static void set_norc(struct options *options)
{
    options->norc_is_set = 1;
}

static void set_ast_print(struct options *options)
{
    options->ast_print_is_set = 1;
}

static void set_set_shopt(struct options *options, int *index, char *argv[])
{

    options->nb_set_shopt++;
    options->set_shopt = realloc(options->set_shopt,
                        options->nb_set_shopt * sizeof(char *));

    options->set_shopt[options->nb_set_shopt - 1] = argv[++(*index)];
}

static void set_unset_shopt(struct options *options, int *index, char *argv[])
{

    options->nb_unset_shopt++;
    options->unset_shopt = realloc(options->unset_shopt,
                        options->nb_unset_shopt * sizeof(char *));

    options->unset_shopt[options->nb_unset_shopt - 1] = argv[++(*index)];
}

int get_option_type(struct options *options, int argc, char *argv[])
{
    if (argc == 0)
        options->no_options = 1;

    for (int i = 0; i < argc; i++)
    {
        char *s = argv[i];

        if (strcmp(s, "-c") == 0)
        {
            if (i + 1 < argc)
                set_command(options, *(argv + i));

            else
            {
                warn("42sh: +O: option requires an argument");
                return OPTIONS_FAILURE;
            }
        }

        else if (strcmp(s, "--norc") == 0)
            set_norc(options);

        else if (strcmp(s, "--ast-print") == 0)
            set_ast_print(options);

        else if (strcmp(s, "-O") == 0)
        {
            if (i + 1 < argc)
                set_set_shopt(options, &i, argv);

            else
            {
                warn("42sh: -O: option requires an argument");
                return OPTIONS_FAILURE;
            }
        }

        else if (strcmp(s, "+O") == 0)
        {
            if (i + 1 < argc)
                set_unset_shopt(options, &i, argv);

            else
            {
                warn("42sh: +O: option requires an argument");
                return OPTIONS_FAILURE;
            }
        }

        // TODO: Add cases for options not implemented yet

        else
        {
            warn("42sh: %s: invalid option", s);
            return OPTIONS_FAILURE;
        }

    }

    return OPTIONS_SUCCESS;
}

void options_free(struct options *options)
{
    free(options->command);
    free(options->set_shopt);
    free(options->set_shopt);
    free(options);
}
