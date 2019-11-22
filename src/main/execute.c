#include "42sh.h"
#include <signal.h>

static int run_lex_parse(struct lexer *lexer, struct execution_bundle *bundle)
{
    struct token_array *arr = lex(lexer);
    printf("[LEXER] done lexing. Got token array: ");
    token_array_print(arr, stdout);
    struct parser *p = parser_init(arr);
    parse(p, bundle->parser_table);
    struct ast *ast = p->ast;
    int return_value = 0;
    if (p->state == PARSER_STATE_SUCCESS)
    {
        if (bundle->shopt->ast_print == 1)
        {
            ast_dot_print(ast, "ast.dot");
        }
        return_value = 1; //do not try to execute ast for now
        //return_value = ast_execute(ast, bundle);
        parser_free(p, 1);
        lexer_clear(lexer);
    }
    else if (p->state == PARSER_STATE_FAILURE)
    {
        return_value = 1;
        parser_free(p, 1);
        lexer_clear(lexer);
    }
    else //if (p->state == PARSER_STATE_CONTINUE)
    {
        parser_free(p, 1);
    }
    token_array_free(arr);

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
        run_lex_parse(lexer, bundle);
    }
    free(line);
    return BASH_RETURN_OK;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    struct lexer *lexer = lexer_init();
    while (1)
    {
        char *ps1 = get_variable(bundle->hash_table_var, "ps1");
        char *ps2 = get_variable(bundle->hash_table_var, "ps2");
        char *input = get_next_line(ps1);
        if (!input)
            break;
        appendhistory(input);
        // run lexer + parser
        lexer_add_string(lexer, input);
        lex(lexer);
        while (lexer->state == LEXER_STATE_LEXING_QUOTES
            || lexer->state == LEXER_STATE_LEXING_DOUBLE_QUOTES
            || lexer->state == LEXER_STATE_UNFINISHED)
        {
            input = get_next_line(ps2);
            if (!input)
                break;
            lexer_add_string(lexer, input);
            lex(lexer);
        }
        run_lex_parse(lexer, bundle);
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
    struct lexer *lexer = lexer_init();
    lexer_add_string(lexer, cmd);
    run_lex_parse(lexer, bundle);
    lexer_free(lexer);
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
    struct lexer *lexer = lexer_init();

    while (getline(&line, &size, fd) != -1)
    {
        lexer_add_string(lexer, line);
        run_lex_parse(lexer, bundle);
        free(line);
    }
    fclose(fd);
    //run lexer + parser
    //token_array_print(arr, stdout);
    return BASH_RETURN_OK;
}
