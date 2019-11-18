#include "execute.h"
#include "42sh.h"
#include <signal.h>

int resetlexer = 0;

void sigintHandler(int _)
{
    if (!_)
        return;
    signal(SIGINT, sigintHandler);
    printf("\n42sh$ ");
    resetlexer++;
    fflush(stdout);
}


int execute_stdin(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    //struct lexer *lexer = lexer_init();
    while (getline(&line, &size, stdin) != -1)
    {
        //run lexer + parser
        struct token_array *arr = token_array_create(line);
        struct ast *ast = tmp_parse(arr);
        if (bundle->options->ast_print_is_set == 1)
        {
            ast_dot_print(ast, "ast.dot");
        }
        ast_execute(ast);
        //token_array_print(arr, stdout);
        token_array_free(arr);
        free(line);
    }
    return BASH_RETURN_OK;
}

int execute_interactive(struct execution_bundle *bundle)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    const char *ps1 = "42sh$ ";
    const char *ps2 = "> ";
    struct lexer *lexer = lexer_init();
    struct token_array *arr = NULL;
    while (1)
    {
        signal(SIGINT, sigintHandler);
        char *input = get_next_line(ps1);
        if (!input)
            break;
        appendhistory(input);
        // run lexer + parser
        lexer_add_string(lexer, input);
        arr = lex(lexer);
        while(lexer->state == STATE_LEXING_QUOTES
            || lexer->state == STATE_LEXING_DOUBLE_QUOTES
            || lexer->state == STATE_UNFINISHED)
        {
            signal(SIGINT, sigintHandler);//TODO Handle this case
            printf("lexer_quotes\n");
            input = get_next_line(ps2);
            if (!input)
                break;
            lexer_add_string(lexer, input);
            token_arrays_fusion(arr, lex(lexer));
        }
        if (lexer->state != STATE_NONE)
            lexer->state = STATE_NONE;
        struct ast *ast = tmp_parse(arr);
        if (bundle->options->ast_print_is_set == 1)
        {
            ast_dot_print(ast, "ast.dot");
        }
        ast_execute(ast);
        //token_array_print(arr, stdout);
        token_array_free(arr);
        free(input);
        resetlexer = 0;
    }
    lexer_clear(lexer);
    return BASH_RETURN_OK;
}

int execute_cmd(struct execution_bundle *bundle, char *cmd)
{
    if (!bundle)
        return BASH_RETURN_ERROR;
    //TODO: load lexer with cmd, run lexing + parsing
    //and return regardless of lexing state
    struct token_array *arr = token_array_create(cmd);
    struct ast *ast = tmp_parse(arr);
    if (bundle->options->ast_print_is_set == 1)
    {
        ast_dot_print(ast, "ast.dot");
    }
    ast_execute(ast);
    //token_array_print(arr, stdout);
    token_array_free(arr);
    return BASH_RETURN_OK;
}

int execute_script(struct execution_bundle *bundle, char* script, int create)
{
    appendhistory(script);
    if (!bundle)
        return BASH_RETURN_ERROR;
    //printf("mode = %s\n", mode);
    FILE *fd;
    fd = fopen(script, "r");
    if (fd == NULL && create == 1)
    {
        fclose(fd);
        fd = fopen(script, "w");
    }
    if (fd == NULL)
    {
        printf("Error no such file or directory %s\n", script);
        return BASH_RETURN_ERROR;
    }
    //TODO: read stdin line by line, running lexing + parsing along the way
    char *line = NULL;
    size_t size;
    struct lexer *lexer = lexer_init();
    struct token_array *arr = token_array_init();

    while (getline(&line, &size, fd) != -1)
    {
        lexer_add_string(lexer, line);
        token_arrays_fusion(arr, lex(lexer));

        free(line);
    }
    fclose(fd);
    //run lexer + parser
    //token_array_print(arr, stdout);
    if (arr->size)
        ast_execute(tmp_parse(arr));

    token_array_free(arr);
    return BASH_RETURN_OK;
}
