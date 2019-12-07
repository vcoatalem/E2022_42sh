#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <time.h>
#include "42sh.h"

void bundle_free(struct execution_bundle *bundle)
{
    if (!bundle)
        return;
    free(bundle->shopt);
    table_free(bundle->parser_table);
    free_hash_table_func(bundle->hash_table_func);
    free_hash_table_var(bundle->hash_table_var);
    free_hash_table_var(bundle->hash_table_aliases);
    lexer_free(bundle->lexer);
    ast_free(bundle->ast);
    parser_free(bundle->parser);
    token_array_free(bundle->token_array);
    options_free(bundle->options);
}

static struct execution_bundle *g_bundle = NULL;


void sig_handler(int val)
{
    if (val == SIGINT)
    {
    }
}

static void set_shellopts_var(struct execution_bundle *bundle)
{
    char *shellsopt = shopt_SHELLOPTS(bundle->shopt);
    insert_variable(bundle->hash_table_var, "SHELLOPTS",
        shellsopt);
    free(shellsopt);
}

static void shell_setup(char *arg0)
{
    time_t t;
    unsigned ut = time(&t);
    srand(ut);
    char absolute_path[4096] = { 0 };
    realpath(arg0, absolute_path);
    setenv("SHELL", absolute_path, 1);
}

int main(int argc, char **argv)
{
    shell_setup(argv[0]);
    signal(SIGINT, sig_handler);
    struct options *options = options_build(argc, argv);
    if (!options)
    {
        return BASH_RETURN_ERROR;
    }
    g_bundle = calloc(1, sizeof(struct execution_bundle));
    struct execution_bundle bundle =
    {
        .options = options,
        .parser_table = table_build(),
        .hash_table_var = init_hash_table_var(50, 1),
        .hash_table_func = init_hash_table_func(50),
        .hash_table_aliases = init_hash_table_var(50, 0),
        .shopt = shopt_init(options),
        .lexer = NULL,
        .parser = NULL,
        .ast = NULL,
        .token_array = NULL,
    };
    set_shellopts_var(&bundle);
    if (options->norc_is_set == 0)
    {
        load_ressource_files(&bundle);
    }
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
    return execution_val;
}
