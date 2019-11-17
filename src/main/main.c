#define _POSIX_C_SOURCE 200809L

#include "42sh.h"
#include <signal.h>
#include "readline.h"
#include "execute.h"


void bundle_free(struct execution_bundle *bundle)
{
    free(bundle->options);
    free(bundle->grammar);
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



int main(int argc, char **argv)
{
    struct options *options = options_build(argc, argv);
    if (!options)
    {
        return BASH_RETURN_OPTIONS_ERROR;
    }
    //struct grammar *g = grammar_build();
    struct execution_bundle bundle = { .options = options,
                                        .grammar = NULL};//g };
    int execution_val = 0;
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
    if (execution_val != BASH_RETURN_OK)
    {
        //something went wrong...
    }
    return BASH_RETURN_OK;
}
