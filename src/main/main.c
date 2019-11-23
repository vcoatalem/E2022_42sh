#define _POSIX_C_SOURCE 200809L

#include <signal.h>

#include "42sh.h"

void bundle_free(struct execution_bundle *bundle)
{
    if (!bundle)
        return;
    free(bundle->shopt);
    table_free(bundle->parser_table);
    free_hash_table_func(bundle->hash_table_func);
    free_hash_table_var(bundle->hash_table_var);
    lexer_free(bundle->lexer);
    ast_free(bundle->ast);
    parser_free(bundle->parser);
    token_array_free(bundle->token_array);
}

static struct execution_bundle *g_bundle = NULL;


void sig_handler(int val)
{
    if (val == SIGINT)
    {
        
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, sig_handler);
    struct options *options = options_build(argc, argv);
    if (!options)
    {
        return BASH_RETURN_OPTIONS_ERROR;
    }
    init_history();
    g_bundle = calloc(1, sizeof(struct execution_bundle));
    struct execution_bundle bundle =
    {  
        .options = options,
        .parser_table = table_build(),
        .hash_table_var = init_hash_table_var(50),
        .hash_table_func = init_hash_table_func(50),
        .shopt = shopt_init(options),
        .lexer = NULL,
        .parser = NULL,
        .ast = NULL,
        .token_array = NULL
    };
    *g_bundle = bundle;
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
        execution_val = execute_script(g_bundle, options->script);
    }
    else if (options->command)
    {
        execution_val = execute_cmd(g_bundle, options->command);
    }
    else if (!isatty(0))
    {
        execution_val = execute_stdin(g_bundle);
    }
    else
    {
        execution_val = execute_interactive(g_bundle);
    }
    if (execution_val != BASH_RETURN_OK)
    {
        //something went wrong...
    }
    bundle_free(g_bundle);
    return BASH_RETURN_OK;
}
