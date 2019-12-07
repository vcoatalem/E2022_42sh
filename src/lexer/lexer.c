#include "lexer.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <err.h>

struct lexer *lexer_init(struct hash_table_var *hash_table_aliases)
{
    struct lexer *lex = calloc(1, sizeof(struct lexer));
    if (!lex)
        err(1, "error while calloc lexer");
    lex->state = LEXER_STATE_NONE;
    lex->str = NULL;
    lex->iterator = 0;
    lex->hash_table_aliases = hash_table_aliases;
    return lex;
}

void lexer_add_string(struct lexer *lexer, char *str)
{
    lexer->state = LEXER_STATE_NONE;
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

static int change_lexer_state(struct lexer *lex)
{
    if (lex->str[lex->iterator] == '\''
        && lex->state != LEXER_STATE_LEXING_QUOTES)
        lex->state = LEXER_STATE_LEXING_QUOTES;
    else if (lex->str[lex->iterator] == '"'
        && lex->state != LEXER_STATE_LEXING_DOUBLE_QUOTES)
        lex->state = LEXER_STATE_LEXING_DOUBLE_QUOTES;
    else if (lex->str[lex->iterator] == '\''
        && lex->state == LEXER_STATE_LEXING_QUOTES)
        {
            lex->state = LEXER_STATE_NONE;
            lex->iterator++;
            return 2;
        }
    else if (lex->str[lex->iterator] == '"'
        && lex->state == LEXER_STATE_LEXING_DOUBLE_QUOTES)
        lex->state = LEXER_STATE_NONE;
    lex->iterator++;
    return 1;
}

static void state_subshell(char *str, size_t *iterator, char *buffer,
        size_t *index, struct token_array *arr)
{
    int cptparentesis = 0;
    enum lexer_state state = LEXER_STATE_SUBSHELL_QUOTE;
    if (buffer[0] == '$' && buffer[1] == '(')
    {
        cptparentesis++;
        state = LEXER_STATE_SUBSHELL_DOL;
        *index = 1;
        buffer[0] = 0;
        buffer[0] = buffer[2];
    }
    if (strcmp(buffer, "`") == 0)
    {
        state = LEXER_STATE_SUBSHELL_QUOTE;
        *index = 0;
        buffer[0] = 0;
    }
    while ((state == LEXER_STATE_SUBSHELL_DOL)
        || state == LEXER_STATE_SUBSHELL_QUOTE)
    {
        buffer[*index] = str[*iterator];
        buffer[*index + 1] = 0;
        *index = *index + 1;
        *iterator = *iterator + 1;
        if (buffer[strlen(buffer) - 1] == '(')
            cptparentesis++;
        if (buffer[strlen(buffer) - 1] == ')')
        {
            cptparentesis--;
        }
        if (buffer[strlen(buffer) - 1] == '`'
            && state == LEXER_STATE_SUBSHELL_QUOTE)
        {
            break;
        }
        if (cptparentesis == 0 && state == LEXER_STATE_SUBSHELL_DOL)
            break;
    }
    if (buffer[strlen(buffer) - 1] == ')' || buffer[strlen(buffer) - 1] == '`')
        buffer[strlen(buffer) - 1] = 0;
    else
        buffer[strlen(buffer) - 2] = 0;
    token_array_add(arr, token_init(TOKEN_SUBSHELL, buffer));
    *index = 0;
}


static void state_arithmetic(char *str, size_t *iterator, char *buffer,
    size_t *index, struct token_array *arr)
{
    int cptparentesis = 0;
    if (buffer[0] == '$' && buffer[1] == '(' && buffer[2] == '(')
    {
        cptparentesis += 2;
        *index = 1;
        buffer[0] = 0;
        buffer[0] = buffer[3];
    }
    while (str[*iterator])
    {
        buffer[*index] = str[*iterator];
        buffer[*index + 1] = 0;
        *index = *index + 1;
        *iterator = *iterator + 1;
        if (buffer[strlen(buffer) - 1] == '(')
            cptparentesis++;
        if (buffer[strlen(buffer) - 1] == ')')
            cptparentesis--;
        if (cptparentesis == 0)
        break;
    }
    if (cptparentesis == 0)
    {
        buffer[strlen(buffer) - 2] = 0;
        token_array_add(arr, token_init(TOKEN_ARITHMETIC, buffer));
        *index = 0;
    }
}

struct token_array *lex(struct lexer *lexer)
{
    char buffer[2048] = { 0 };
    struct token_array *arr = token_array_init();
    size_t index = 0;
    enum token_type type = TOKEN_EOF;
    int is_string = 0;

    while (lexer->str[lexer->iterator] != 0)
    {
        if (lexer->state != LEXER_STATE_LEXING_QUOTES && ((strlen(buffer) >= 3
            && ((buffer[0] == '$' && buffer[1] == '('
            && buffer[2] != '('))) || strcmp(buffer, "`") == 0))
        {
            state_subshell(lexer->str, &lexer->iterator, buffer, &index, arr);
        }
        else if (lexer->state != LEXER_STATE_LEXING_QUOTES && strlen(buffer) >= 4
            && buffer[0] == '$' && buffer[1] == '(' && buffer[2] == '(')
        {
            state_arithmetic(lexer->str, &lexer->iterator, buffer, &index, arr);
        }
        else if ((lexer->str[lexer->iterator] == '"'
            && lexer->state != LEXER_STATE_LEXING_QUOTES)
            || (lexer->str[lexer->iterator] == '\''
                && lexer->state != LEXER_STATE_LEXING_DOUBLE_QUOTES))
        {
            is_string = change_lexer_state(lexer);
        }
        else if (is_separator(lexer->str[lexer->iterator])
            && (lexer->state == LEXER_STATE_NONE) && ((buffer[0] != '$')
            || (strlen(buffer) > 1 && buffer[1] != '(')))
        {
            handle_separators(lexer->str, &lexer->iterator, buffer, &index,
                    arr, is_string, lexer->hash_table_aliases);
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
                if (is_string)
                    token->quoted = 1;
                token_array_add(arr, token);
                index = 0;
            }
            is_string = 0;
        }
    }
    if (index > 0)
    {
        if (is_string == 2)
        {
            type = TOKEN_WORD_NO_SUBSTITUTION;
        }
        else
            type = token_check(buffer, 0, buffer);
        if (type != TOKEN_WORD && is_string == 1)
            token_array_add(arr, token_init(TOKEN_WORD, buffer));
        else if (type != TOKEN_WORD && is_string == 2)
            token_array_add(arr, token_init(TOKEN_WORD_NO_SUBSTITUTION, buffer));
        else if (type == TOKEN_WORD)
            check_assignment(buffer, arr, is_string, lexer->hash_table_aliases);
        else
            token_array_add(arr, token_init(type, buffer));
    }
    if (lexer->state == LEXER_STATE_NONE)
    {
        //lexing is done; adding final EOF and applying post treatments
        //for further processing
        token_array_add(arr, token_init(TOKEN_EOF, ""));
        post_lexing_treatment(arr);
    }
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
