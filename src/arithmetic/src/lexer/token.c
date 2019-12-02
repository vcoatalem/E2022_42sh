#include "lexer/token.h"
#include "utils/xalloc.h"

#include <stdio.h>
#include <stdlib.h>

const char *arithmetic_token_str(struct arithmetic_token *token)
{
    static const char *token_strs[] = { "+", "-", "*", "/", "(", ")", "EOF" };
    static char number_str[11];

    if (token->type != TOKEN_NUMBER)
        return token_strs[token->type];

    sprintf(number_str, "%d", token->value);
    return number_str;
}

struct arithmetic_token *arithmetic_token_alloc(void)
{
    struct arithmetic_token *res = xmalloc(sizeof(*res));
    res->type = TOKEN_EOF;
    res->value = 0;

    return res;
}

void arithmetic_token_free(struct arithmetic_token *token)
{
    free(token);
}
