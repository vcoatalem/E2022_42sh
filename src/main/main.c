#define _POSIX_C_SOURCE 200809L

#include "42sh.h"
#include <signal.h>
#include "readline.h"


void bundle_free(struct execution_bundle *bundle)
{
    free(bundle->options);
    free(bundle->grammar);
    free_hash_table_func(bundle->hash_table_func);
    free_hash_table_var(bundle->hash_table_var);
}


void appendhistory(char *cmd)
{
    FILE *fd = fopen(".42sh_history", "at");
    if (!fd)
        fd = fopen(".42sh_history", "wt");
    if (!fd)
    {
        return;
    }

    fputs(cmd, fd);
    fputs("\n", fd);

    fclose(fd);
}

/*
static int check_file_exist(char* path)
{
    FILE *fd;
    fd = fopen(path,"r");
    if (!fd)
        return 0;
    fclose(fd);
    return 1;
}*/



int main(int argc, char **argv)
{
    struct options *options = options_build(argc, argv);
    if (!options)
    {
        return BASH_RETURN_OPTIONS_ERROR;
    }
    //struct grammar *g = grammar_build();
    struct execution_bundle bundle = { .options = options,
                                        .grammar = NULL,
                                        .hash_table_var = init_hash_table_var(50),
                                        .hash_table_func = init_hash_table_func(50)};//g };
    int execution_val = 0;
    /*if (!options->norc_is_set)
    {
        if (check_file_exist("/etc/42shrc"))
            execute_script(&bundle, "/etc/42shrc");
        if (check_file_exist(".42shrc"))
            execute_script(&bundle, ".42shrc");
        //execute_script(&bundle, ".42shrc", 1);
        //execute_script(&bundle, "/etc/42shrc", 1);
        //execute_script(&bundle, ".42shrc", 1);
        //execution_val = (execute_script(&bundle, "/42shrc.txt", "r+"));
    }*/

    if (options->script != NULL)
    {
        execution_val = execute_script(&bundle, options->script);
    }
    else if (options->command)
    {
        execution_val = execute_cmd(&bundle, options->command);
    }
    else if (!isatty(0))
    {
        execution_val = execute_stdin(&bundle);
    }
    else
    {
        execution_val = execute_interactive(&bundle);
    }
    options_free(options);
    bundle_free(&bundle);
    if (execution_val != BASH_RETURN_OK)
    {
        //something went wrong...
    }
    return BASH_RETURN_OK;
}
