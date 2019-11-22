#include "42sh.h"
#include <signal.h>

static int run_lex_parse(struct execution_bundle *bundle)
{
    if (bundle->token_array)
        token_array_free(bundle->token_array);
    bundle->token_array = lex(bundle->lexer);
    printf("[LEXER] done lexing. Got token array: ");
    token_array_print(bundle->token_array, stdout);
    
    if (bundle->parser)
        parser_free(bundle->parser);
    bundle->parser = parser_init(bundle->token_array);
    
    parse(bundle->parser, bundle->parser_table);
    
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
        return_value = 1; //do not try to execute ast for now
        //return_value = ast_execute(ast, bundle);
        lexer_clear(bundle->lexer);
    }
    else if (bundle->parser->state == PARSER_STATE_FAILURE)
    {
        return_value = 1;
        lexer_clear(bundle->lexer);
    }
    else //if (p->state == PARSER_STATE_CONTINUE)
    {
    }
    printf("lexing parsing process returning: %d\n", return_value);
    return return_value;
}


int execute_stdin(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    struct lexer *lexer = lexer_init();
    while (getline(&line, &size, stdin) != -1)
    {
        lexer_add_string(lexer, line);
        run_lex_parse(bundle);
    }
    free(line);
    return BASH_RETURN_OK;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    bundle->lexer = lexer_init();
    while (1)
    {
        char *ps1 = get_variable(bundle->hash_table_var, "ps1");
        char *ps2 = get_variable(bundle->hash_table_var, "ps2");
        char *input = get_next_line(ps1);
        if (!input)
            break;
        appendhistory(input);
        // run lexer + parser
        lexer_add_string(bundle->lexer, input);
        struct token_array *try_lex = lex(bundle->lexer);
        while (bundle->lexer->state == LEXER_STATE_LEXING_QUOTES
            || bundle->lexer->state == LEXER_STATE_LEXING_DOUBLE_QUOTES
            || bundle->lexer->state == LEXER_STATE_UNFINISHED)
        {
            input = get_next_line(ps2);
            if (!input)
                break;
            lexer_add_string(bundle->lexer, input);
            struct token_array *arr = lex(bundle->lexer);
            token_array_free(arr);
        }
        token_array_free(try_lex);
        run_lex_parse(bundle);
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
    run_lex_parse(bundle);
    return BASH_RETURN_OK;
}

int execute_script(struct execution_bundle *bundle, char* script)
{
    appendhistory(script);
    if (!bundle)
        return BASH_RETURN_ERROR;
    //printf("mode = %s\n", mode);
    FILE *fd;
    fd = fopen(script, "r");
    if (fd == NULL)
    {
        printf("Error no such file or directory %s\n", script);
        return BASH_RETURN_ERROR;
    }
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    bundle->lexer = lexer_init();
    while (getline(&line, &size, fd) != -1)
    {
        lexer_add_string(bundle->lexer, line);
        run_lex_parse(bundle);
        free(line);
    }
    fclose(fd);
    //run lexer + parser
    //token_array_print(arr, stdout);
    return BASH_RETURN_OK;
}
