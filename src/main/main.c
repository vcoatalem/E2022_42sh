#define _POSIX_C_SOURCE 200809L

#include "42sh.h"

enum BASH_RETURN_VALUES
{
    BASH_RETURN_OK = 0,
    BASH_RETURN_ERROR = 1,
    BASH_RETURN_OPTIONS_ERROR = 2
};

struct execution_bundle
{
    struct options *options;
    struct grammar *grammar;
};

void bundle_free(struct execution_bundle *bundle)
{
    free(bundle->options);
    free(bundle->grammar);
}

static int execute_stdin(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, stdin) != -1)
    {
        //run lexer + parser
        struct token_array *arr = token_array_create(line);
        token_array_print(arr, stdout);
        token_array_free(arr);
        free(line);
    }
    return BASH_RETURN_OK;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    const char *ps1 = "42sh ";
    const char *ps2 = "> ";
    struct lexer *lexer = lexer_init();
    while (1)
    {
        char *input = readline(ps1);
        if (!input)
            break;
        // run lexer + parser
        lexer_add_string(lexer, input);
        struct token_array *arr = lex(lexer);

        while(lexer->state == STATE_LEXING_QUOTES
            || lexer->state == STATE_LEXING_DOUBLE_QUOTES
            || lexer->state == STATE_UNFINISHED)
        {
            input = readline(ps2);
            if (!input)
                break;
            lexer_add_string(lexer, input);
            token_arrays_fusion(arr, lex(lexer));
        }


        token_array_print(arr, stdout);
        token_array_free(arr);
        free(input);
    }
    lexer_clear(lexer);
    return BASH_RETURN_OK;
}

int execute_cmd(struct execution_bundle *bundle, char *cmd)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: load lexer with cmd, run lexing + parsing and return regardless of lexing state
    struct token_array *arr = token_array_create(cmd);
    token_array_print(arr, stdout);
    token_array_free(arr);
    return BASH_RETURN_OK;
}

int main(int argc, char **argv)
{
    struct options *options = options_build(argc, argv);
    if (!options)
    {
        return BASH_RETURN_OPTIONS_ERROR;
    }
    struct grammar *g = grammar_build();
    struct execution_bundle bundle = { .options = options,
                                        .grammar = g };
    int execution_val = 0;
    if (options->command)
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
