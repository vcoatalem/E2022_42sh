#ifndef OPTIONS_H
#define OPTIONS_H

#include <stddef.h>

struct options
{
    int no_options;

    size_t nb_command;
    char **command;

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

void free_options(struct options *options);

#endif /* OPTIONS_H */
