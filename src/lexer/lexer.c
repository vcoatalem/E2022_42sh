#include "lexer.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <err.h>

struct lexer *lexer_init(void)
{
    struct lexer *lex= calloc(1, sizeof(struct lexer));
    if (!lex)
        err(1, "error while calloc lexer");
    lex->state = STATE_NONE;
    lex->str = calloc(1, sizeof(char*));
    if (!lex->str)
        err(1, "error while calloc lex->str");
    //lex->str = "";
    lex->iterator = 0;
    return lex;
}

void lexer_add_string(struct lexer *lexer, char *str)
{
    size_t lena = strlen(lexer->str);
    size_t lenb = strlen(str);
    size_t len = lena + lenb + 1;
    lexer->str = realloc(lexer->str, len);
    memcpy(lexer->str + lena, str, lenb + 1);
}

void lexer_clear(struct lexer *lexer)
{
    free(lexer->str);
    free(lexer);
}

void change_lexer_state(struct lexer *lex)
{
    if ((lex->state == STATE_LEXING_DOUBLE_QUOTES && lex->str[lex->iterator] == '\'')
        || (lex->state == STATE_LEXING_QUOTES && lex->str[lex->iterator] == '"'))
        return;
    else if (lex->str[lex->iterator] == '\'' && lex->state != STATE_LEXING_QUOTES)
        lex->state = STATE_LEXING_QUOTES;
    else if (lex->str[lex->iterator] == '"' && lex->state != STATE_LEXING_DOUBLE_QUOTES)
        lex->state = STATE_LEXING_DOUBLE_QUOTES;
    else if (lex->str[lex->iterator] == '\'' && lex->state == STATE_LEXING_QUOTES)
        lex->state = STATE_NONE;
    else if (lex->str[lex->iterator] == '"' && lex->state == STATE_LEXING_DOUBLE_QUOTES)
        lex->state = STATE_NONE;
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
        if (lexer->str[lexer->iterator] == '"' || lexer->str[lexer->iterator] == '\'')
            change_lexer_state(lexer);
        else if (is_separator(lexer->str[lexer->iterator]) && lexer->state == STATE_NONE)
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
            if (type != TOKEN_WORD && is_separator(lexer->str[lexer->iterator]) && lexer->state == STATE_NONE)
            {
                struct token *token = token_init(type, buffer);
                token_array_add(arr, token);
                index = 0;
            }
        } 
    }
    if (lexer->state != STATE_NONE)//If waiting " or ' we add \n to buffer
    {
        buffer[index] = '\n';
        index++;
        buffer[index] = 0;
    }
    if (index > 0)
    {
        token_array_add(arr, token_init(token_check(buffer, 0, buffer), buffer));
    }
    if (lexer->state == STATE_NONE)
        token_array_add(arr, token_init(TOKEN_EOF, ""));;
    return arr;
    //return token_array_create(lexer->str);
}