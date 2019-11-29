/**
 * \file options.h
 * \brief file with definition of options structure and its functions
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 21th 2019
 *
 * Options structure used when launching 42sh
 *
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stddef.h>

#define OPTIONS_SUCCESS 1
#define OPTIONS_FAILURE 0

/**
 * \struct options
 * \brief options structure
 *
 * Contain all checkmark for if an option is set or not, and its arguments
 *
 */
struct options
{
    int no_options;

    char *command;

    int norc_is_set;

    int ast_print_is_set;

    int print_shopt_is_set;

    size_t nb_set_shopt;
    char **set_shopt;

    size_t nb_unset_shopt;
    char **unset_shopt;

    char **args;
    int begargs;

    char *script;

    // TODO: Add options not implemented yet
};

/**
 * \brief initialize the options structure
 *
 * \return options return a new options structure
 */
struct options *options_init(void);

/**
 * \brief get all options and set the options structure accordingly
 *
 * \param options options to set
 * \param argc number of arguments
 * \param argv list of arguments
 *
 * \return int return true or false if error
 */
int get_option_type(struct options *options, int argc, char *argv[]);

/**
 * \brief free the options structure from memory
 *
 * \param options options structure to free
 */
void options_free(struct options *options);

/**
 * \brief create and set an options structure
 *
 * \param args number of arguments
 * \param argv list of arguments
 *
 * \return options return a new options structure with all options set
 */
struct options *options_build(int argc, char **argv);

#endif /* OPTIONS_H */
