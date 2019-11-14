#include "options.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int nb_argc(char *argv[])
{
    int nb = 0;

    for (; argv[nb] != NULL; nb++)
        continue;

    return nb;
}

int options_is_equal(struct options *opt1, struct options *opt2)
{
    if (opt1->no_options != opt2->no_options
            || opt1->nb_command != opt2->nb_command
            || opt1->norc_is_set != opt2->norc_is_set
            || opt1->ast_print_is_set != opt2->ast_print_is_set
            || opt1->nb_set_shopt != opt2->nb_set_shopt
            || opt1->nb_unset_shopt != opt2->nb_unset_shopt)
        return 1;

    for (size_t i = 0; i < opt1->nb_command; i++)
    {
        if (strcmp(opt1->command[i], opt2->command[i]) != 0)
            return 1;
    }

    for (size_t i = 0; i < opt1->nb_set_shopt; i++)
    {
        if (strcmp(opt1->set_shopt[i], opt2->set_shopt[i]) != 0)
            return 1;
    }

    for (size_t i = 0; i < opt1->nb_unset_shopt; i++)
    {
        if (strcmp(opt1->unset_shopt[i], opt2->unset_shopt[i]) != 0)
            return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int q = (argc == 1 ? 0 : atoi(*(argv + 1)));

    char *cmd1[] = { "-c", "ls", NULL };
    char *cmd2[] = { "-c", NULL };
    char *cmd3[] = { "+O", "sourcepath", NULL };
    char *cmd4[] = { "+O", "mailwarn", NULL };
    char *cmd5[] = { "-O", "failglob", NULL };
    char *cmd6[] = { "-O", NULL };
    char *cmd7[] = { "--norc", NULL };
    char *cmd8[] = { "--ast-print", NULL };
    char *cmd9[] = { "-c", "ls", "--ast-print", NULL };
    char *cmd10[] = { "--norc", "-c", "-23", "-a", "echo foo", NULL };
    char *cmd11[] = { NULL };

    char **cmd[] =
    {
        cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9,
        cmd10, cmd11
    };

    struct options *options_input = options_init();
    struct options *options_output = options_init();

    for (size_t i = 0; *(cmd[q] + i); i++)
    {
        printf(" %s", *(cmd[q] + i));
    }
    fflush(stdout);
    if (q == 0)
    {
        options_output->nb_command = 1;
        options_output->command = malloc(sizeof(char *));
        options_output->command[0] = "ls";
    }

    if (q == 2)
    {
        options_output->nb_unset_shopt = 1;
        options_output->unset_shopt = malloc(sizeof(char **));
        options_output->unset_shopt[0] = "sourcepath";
    }

    if (q == 3)
    {
        options_output->nb_unset_shopt = 1;
        options_output->unset_shopt = malloc(sizeof(char **));
        options_output->unset_shopt[0] = "mailwarn";
    }

    if (q == 4)
    {
        options_output->nb_set_shopt = 1;
        options_output->set_shopt = malloc(sizeof(char **));
        options_output->set_shopt[0] = "failglob";
    }

    if (q == 6)
        options_output->norc_is_set = 1;

    if (q == 7)
        options_output->ast_print_is_set = 1;

    if (q == 8)
    {
        options_output->nb_command = 1;
        options_output->command = malloc(sizeof(char **));
        options_output->command[0] = "ls";
        options_output->ast_print_is_set = 1;
    }

    if (q == 9)
    {
        options_output->norc_is_set = 1;
        options_output->nb_command = 1;
        options_output->command = malloc(sizeof(char **));
        options_output->command[0] = "echo foo";
    }

    get_option_type(options_input, nb_argc(cmd[q]), cmd[q]);

    #if 0 // PRINT CONTENT OF EXEMPLES
    printf("input_no_options = %d\n", options_input->no_options);
    printf("output_no_options = %d\n\n", options_output->no_options);

    printf("input_nb_command = %ld\n", options_input->nb_command);
    printf("output_nb_command = %ld\n\n", options_output->nb_command);

    for (size_t i = 0; i < options_input->nb_command; i++)
        printf("%s <> %s\n", options_input->command[i], options_output->command[i]);

    printf("input_norc_is_set = %d\n", options_input->norc_is_set);
    printf("output_norc_is_set = %d\n\n", options_output->norc_is_set);

    printf("input_ast_print_is_set = %d\n", options_input->ast_print_is_set);
    printf("output_ast_print_is_set = %d\n\n", options_output->ast_print_is_set);

    printf("input_nb_set_shopt = %ld\n", options_input->nb_set_shopt);
    printf("output_nb_set_shopt = %ld\n\n", options_output->nb_set_shopt);

    for (size_t i = 0; i < options_input->nb_set_shopt; i++)
        printf("%s <> %s\n", options_input->set_shopt[i], options_output->set_shopt[i]);

    printf("input_nb_unset_shopt = %ld\n", options_input->nb_unset_shopt);
    printf("output_nb_unset_shopt = %ld\n", options_output->nb_unset_shopt);

    for (size_t i = 0; i < options_input->nb_unset_shopt; i++)
        printf("%s <> %s\n", options_input->unset_shopt[i], options_output->unset_shopt[i]);
    #endif

    assert(options_is_equal(options_input, options_output) == 0);

    free_options(options_input);
    free_options(options_output);

    return 0;
}
