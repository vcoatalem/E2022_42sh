#include "options.h"
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>

struct options *options_init(void)
{
    struct options *new_options = malloc(sizeof(struct options));

    if (new_options == NULL)
        err(errno, "ERROR_OPTIONS_INIT: Cannot allocate memory.");

    new_options->no_options = 0;

    new_options->nb_command = 0;
    new_options->command = NULL;

    new_options->norc_is_set = 0;

    new_options->ast_print_is_set = 0;

    new_options->nb_set_shopt = 0;
    new_options->set_shopt = NULL;

    new_options->nb_unset_shopt = 0;
    new_options->unset_shopt = NULL;

    return new_options;
}

int get_option_type(struct options *options, int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *s = argv[i];

        if (strcmp(s, "-c") == 0)
        {
            options->nb_command++;
            options->command = realloc(options->command,
                                        options->nb_command * sizeof(char *));
            options->command[options->nb_command - 1] = argv[++i];
            break;
        }

        else if (strcmp(s, "--norc") == 0)
        {
            options->norc_is_set = 1;
            break;
        }

        else if (strcmp(s, "--ast-print") == 0)
        {
            options->ast_print_is_set = 1;
            break;
        }

        else if (strcmp(s, "-O") == 0)
        {
            options->nb_set_shopt++;
            options->set_shopt = realloc(options->set_shopt,
                                    options->nb_set_shopt * sizeof(char *));
            options->set_shopt[options->nb_set_shopt - 1] = argv[++i];
            break;
        }

        else if (strcmp(s, "+O") == 0)
        {
            options->nb_unset_shopt++;
            options->unset_shopt = realloc(options->unset_shopt,
                                    options->nb_unset_shopt * sizeof(char *));
            options->unset_shopt[options->nb_unset_shopt - 1] = argv[++i];
            break;
        }

        // TODO: Add case for option not implemented yet

        else
            err(2, "42sh: %s: invalid option", s);
    }

    return 0;
}

void free_options(struct options *options)
{
    for (size_t i = 0; i < options->nb_command; i++)
    {
        free(options->command[i]);
        options->command[i] = NULL;
    }

    for (size_t i = 0; i < options->nb_set_shopt; i++)
    {
        free(options->set_shopt[i]);
        options->set_shopt[i] = NULL;
    }

    for (size_t i = 0; i < options->nb_unset_shopt; i++)
    {
        free(options->unset_shopt[i]);
        options->unset_shopt[i] = NULL;
    }

    free(options);
    options = NULL;
}

int main(int argc, char *argv[])
{
    struct options *options = options_init();

    if (argc == 1)
        options->no_options = 1;

    get_option_type(options, argc, argv);
    free_options(options);

    return 0;
}
