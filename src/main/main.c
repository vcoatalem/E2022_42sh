#define _POSIX_C_SOURCE 200809L

#include "42sh.h"

enum BASH_RETURN_VALUES
{
    BASH_RETURN_OK = 0,
    BASH_RETURN_ERROR = 1,
    BASH_RETURN_WRONG_FLAG = 2
};

struct execution_bundle
{
    struct options *options;
    struct grammar *grammar;
};

static int execute_stdin(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, stdin) != -1)
    {
        printf("%s\n", line);
        free(line);
    }
    return BASH_RETURN_OK;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    const char *ps1 = "42sh ";
    //const char *ps2 = "> ";
    while (1)
    {
        char *input = readline(ps1);
        // run lexer + parser
        struct token_array *arr = token_array_create(input);
        token_array_print(arr, stdout);
        free(input);
    }
    return BASH_RETURN_OK;
}

int execute_cmd(struct execution_bundle *bundle, char *cmd)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: load lexer with cmd, run lexing + parsing and return regardless of lexing state
    struct token_array *arr = token_array_create(cmd);
    token_array_print(arr, stdout);
    return BASH_RETURN_OK;
}

int main(int argc, char **argv)
{
    struct options *options = options_init();
    if (argc > 2)
    {
        int get_options = get_option_type(options, argc, argv + 1);
        if (get_options == OPTIONS_FAILURE)
        {
            options_free(options);
            return BASH_RETURN_WRONG_FLAG;
        }
    }
    struct grammar *g = grammar_build();
    struct execution_bundle bundle = { .options = options,
                                        .grammar = g };
    int execution_val = 0;
    if (options->command)
    {
        execution_val = execute_cmd(&bundle, options->command);
    }
    if (isatty(0))
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
    grammar_free(g);
    return BASH_RETURN_OK;
}
