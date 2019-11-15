#ifndef OPTIONS_H
#define OPTIONS_H

#include <stddef.h>

#define OPTIONS_SUCCESS 1
#define OPTIONS_FAILURE 0

struct options
{
    int no_options;

    char *command;

    int norc_is_set;

    int ast_print_is_set;

    size_t nb_set_shopt;
    char **set_shopt;

    size_t nb_unset_shopt;
    char **unset_shopt;

    // TODO: Add options not implemented yet
};

struct options *options_init(void);

int get_option_type(struct options *options, int argc, char *argv[]);

void options_free(struct options *options);

struct options *options_build(int argc, char **argv);

#endif /* OPTIONS_H */
