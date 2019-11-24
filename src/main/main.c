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
    init_history(&bundle);
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
    bundle_free(g_bundle);
    if (execution_val != BASH_RETURN_OK)
    {
        return execution_val;
        //something went wrong...
    }
    return BASH_RETURN_OK;
}
