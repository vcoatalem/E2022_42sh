#include "lexer.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <err.h>

struct lexer *lexer_init(void)
{
    struct lexer *lex = calloc(1, sizeof(struct lexer));
    if (!lex)
        err(1, "error while calloc lexer");
    lex->state = LEXER_STATE_NONE;
    lex->str = NULL;
    lex->iterator = 0;
    return lex;
}

void lexer_add_string(struct lexer *lexer, char *str)
{
    size_t len_str = strlen(str);
    if (!lexer->str)
    {
        lexer->str = calloc(1, strlen(str) + 1);
        strcpy(lexer->str, str);
        *(lexer->str + len_str) = 0;
    }
    else
    {
        size_t len_dst = strlen(lexer->str);
        lexer->str = realloc(lexer->str,
                len_dst + len_str + 2);
        *(lexer->str + len_dst) = '\n';
        strcpy(lexer->str + len_dst + 1, str);
        *(lexer->str + len_dst + len_str + 1) = 0;
    }
}

void lexer_clear(struct lexer *lexer)
{
    free(lexer->str);
    lexer->str = NULL;
    lexer->iterator = 0;
    lexer->state = LEXER_STATE_NONE;
}

void change_lexer_state(struct lexer *lex)
{
    if ((lex->state == LEXER_STATE_LEXING_DOUBLE_QUOTES
        && lex->str[lex->iterator] == '\'')
        || (lex->state == LEXER_STATE_LEXING_QUOTES
            && lex->str[lex->iterator] == '"'))
        return;
    else if (lex->str[lex->iterator] == '\''
        && lex->state != LEXER_STATE_LEXING_QUOTES)
        lex->state = LEXER_STATE_LEXING_QUOTES;
    else if (lex->str[lex->iterator] == '"'
        && lex->state != LEXER_STATE_LEXING_DOUBLE_QUOTES)
        lex->state = LEXER_STATE_LEXING_DOUBLE_QUOTES;
    else if (lex->str[lex->iterator] == '\''
        && lex->state == LEXER_STATE_LEXING_QUOTES)
        lex->state = LEXER_STATE_NONE;
    else if (lex->str[lex->iterator] == '"'
        && lex->state == LEXER_STATE_LEXING_DOUBLE_QUOTES)
        lex->state = LEXER_STATE_NONE;
    lex->iterator++;
}

struct token_array *lex(struct lexer *lexer)
{
    char buffer[2048] = { 0 };
    struct token_array *arr = token_array_init();
    size_t index = 0;
    enum token_type type = TOKEN_EOF;
    while (lexer->str[lexer->iterator] != 0)
    {
        if (lexer->str[lexer->iterator] == '"'
            || lexer->str[lexer->iterator] == '\'')
            change_lexer_state(lexer);
        else if (is_separator(lexer->str[lexer->iterator])
            && lexer->state == LEXER_STATE_NONE)
        {
            handle_separators(lexer->str, &lexer->iterator, buffer, &index, arr);
        }
        else
        {
            buffer[index] = lexer->str[lexer->iterator];
            buffer[index + 1] = 0;
            index++;
            lexer->iterator++;
            type = token_check(lexer->str, lexer->iterator, buffer);
            if (type != TOKEN_WORD && is_separator(lexer->str[lexer->iterator])
                && lexer->state == LEXER_STATE_NONE)
            {
                struct token *token = token_init(type, buffer);
                token_array_add(arr, token);
                index = 0;
            }
        }
    }
    #if 0
    if (lexer->state != LEXER_STATE_NONE)
    {
        buffer[index] = '\n';
        index++;
        buffer[index] = 0;
    }
    #endif
    if (index > 0)
    {
        token_array_add(arr, token_init(
            token_check(buffer, 0, buffer), buffer));
    }
    if (lexer->state == LEXER_STATE_NONE)
        token_array_add(arr, token_init(TOKEN_EOF, ""));
    //reset the iterator in case we need to 
    lexer->iterator = 0;
    return arr;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;
    free(lexer->str);
    free(lexer);
}
