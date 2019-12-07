#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "token.h"

struct token *token_init(enum token_type type, char *value)
{
    struct token *res = malloc(sizeof(struct token));
    if (!res)
        return NULL;
    res->type = type;
    res->value = calloc(1, strlen(value) + 1);
    res->quoted = 0;
    strcpy(res->value, value);
    return res;
}

void token_free(struct token *token)
{
    free(token->value);
    free(token);
}

int token_is_word(struct token *token)
{
    return token->type == TOKEN_WORD
        || token->type == TOKEN_WORD_EXPAND
        || token->type == TOKEN_SUBSHELL
        || token->type == TOKEN_ARITHMETIC
        || token->type == TOKEN_WORD_TILDE;
}
