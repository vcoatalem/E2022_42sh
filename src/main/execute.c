#include <err.h>
#include "42sh.h"

static int run_lex_parse(struct execution_bundle *bundle)
{
    if (bundle->token_array)
        token_array_free(bundle->token_array);
    bundle->token_array = lex(bundle->lexer);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[LEXER] done lexing. Got token array: ");
        token_array_print(bundle->token_array, stdout);
    }
    if (bundle->parser)
        parser_free(bundle->parser);
    bundle->parser = parser_init(bundle->token_array, bundle->parser_table);
    //call main parsing function here
    parse(bundle->parser, bundle);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[PARSER] parser state: %d\n", bundle->parser->state);
    }
    if (bundle->ast)
        ast_free(bundle->ast);
    bundle->ast = bundle->parser->ast;
    int return_value = 0;
    if (bundle->parser->state == PARSER_STATE_SUCCESS)
    {
        if (bundle->shopt->ast_print == 1)
        {
            ast_dot_print(bundle->ast, "ast.dot");
        }
        return_value = ast_execute(bundle->ast, bundle);
        lexer_clear(bundle->lexer);
    }
    else if (bundle->parser->state == PARSER_STATE_FAILURE)
    {
        return_value = BASH_RETURN_ERROR;
        lexer_clear(bundle->lexer);
    }
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[EXECUTION] lex+parse returning: %d\n", return_value);
    }
    return return_value;
}

int execute_stdin(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //read stdin line by line, running lexing + parsing along the way
    int return_value = BASH_RETURN_OK;
    char *line = NULL;
    size_t size;
    bundle->lexer = lexer_init();
    while (getline(&line, &size, stdin) != -1)
    {
        //stripping final EOL from line
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        lexer_add_string(bundle->lexer, line);
        return_value = run_lex_parse(bundle);
    }
    free(line);
    return return_value;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    bundle->lexer = lexer_init();
    char *ps1 = get_variable(bundle->hash_table_var, "PS1");
    char *ps2 = get_variable(bundle->hash_table_var, "PS2");
    char *prompt = ps1;
    while (1)
    {
        char *input = get_next_line(prompt);
        if (!input)
            break;
        appendhistory(input, bundle);
        // run lexer + parser
        lexer_add_string(bundle->lexer, input);
        struct token_array *try_lex = lex(bundle->lexer);
        while (bundle->lexer->state == LEXER_STATE_LEXING_QUOTES
            || bundle->lexer->state == LEXER_STATE_LEXING_DOUBLE_QUOTES
            || bundle->lexer->state == LEXER_STATE_UNFINISHED)
        {
            char *input1 = get_next_line(ps2);
            if (!input)
                break;
            lexer_add_string(bundle->lexer, input1);
            struct token_array *arr = lex(bundle->lexer);
            token_array_free(arr);
            free(input1);
        }
        token_array_free(try_lex);
        run_lex_parse(bundle);
        //set prompt for next iteration
        if (bundle->parser->state == PARSER_STATE_CONTINUE)
            prompt = ps2;
        else
            prompt = ps1;
        free(input);
    }
    return BASH_RETURN_OK;
}

int execute_cmd(struct execution_bundle *bundle, char *cmd)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: load lexer with cmd, run lexing + parsing
    //and return regardless of lexing state
    bundle->lexer = lexer_init();
    lexer_add_string(bundle->lexer, cmd);
    int try_execute = run_lex_parse(bundle);
    return try_execute;
}

static void set_hash_var_args(struct execution_bundle *bundle)
{
    if (bundle->options->begargs)
    {
        for (int i = 0; bundle->options->args[i]; ++i)
        {
            char el[64];
            sprintf(el, "%d", i);
            insert_variable(bundle->hash_table_var, el,
                strdup(bundle->options->args[i]));
        }

        char allparams[2048] = {0};
        int cpt = 0;
        int i = bundle->options->begargs;
        for (; bundle->options->args[i]; ++i)
        {
            int cptarg = 0;
            while(bundle->options->args[i][cptarg])
            {
                allparams[cpt] = bundle->options->args[i][cptarg];
                cptarg++;
                cpt++;
            }
            allparams[cpt] = ' ';
            cpt++;
        }
        insert_variable(bundle->hash_table_var, "@", allparams);
        insert_variable(bundle->hash_table_var, "*", allparams);
        char el[64];
        sprintf(el, "%d", i - bundle->options->begargs);
        insert_variable(bundle->hash_table_var, "#", el);
    }
}


int execute_script(struct execution_bundle *bundle, char *script)
{
    appendhistory(script, bundle);
    if (!bundle)
        return BASH_RETURN_ERROR;

    set_hash_var_args(bundle);

    int return_value = BASH_RETURN_ERROR;
    FILE *fd;
    fd = fopen(script, "r");
    if (fd == NULL)
    {
        warnx("Could not open file `%s` for execution", script);
        return BASH_RETURN_ERROR;
    }
    // read file line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    bundle->lexer = lexer_init();
    while (getline(&line, &size, fd) != -1)
    {
        //stripping final EOL from line
        line[strlen(line) - 1] = 0;
        lexer_add_string(bundle->lexer, line);
        return_value = run_lex_parse(bundle);
    }
    free(line);
    fclose(fd);
    return return_value;
}
