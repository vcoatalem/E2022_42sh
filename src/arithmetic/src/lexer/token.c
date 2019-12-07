#include "lexer/token.h"
#include "utils/xalloc.h"

#include <stdio.h>
#include <stdlib.h>

const char *arithmetic_token_str(struct arithmetic_token *token)
{
    static const char *token_strs[] = { "+", "-", "*", "/", "(", ")",
            "&", "|", "^", "&&", "||", "**", "!", "~", "EOF" };
    static char number_str[11];

    if (token->type != A_TOKEN_NUMBER)
        return token_strs[token->type];

    sprintf(number_str, "%d", token->value);
    return number_str;
}

struct arithmetic_token *arithmetic_token_alloc(void)
{
    struct arithmetic_token *res = xmalloc(sizeof(*res));
    res->type = A_TOKEN_EOF;
    res->value = 0;

    return res;
}

void arithmetic_token_free(struct arithmetic_token *token)
{
    free(token);
}

char *a_token_str(enum arithmetic_token_type type)
{
    switch (type)
    {
    case A_TOKEN_PLUS:
        return "+";
    case A_TOKEN_MINUS:
        return "-";
    case A_TOKEN_MULTIPLY:
        return "*";
    case A_TOKEN_DIVIDE:
        return "/";
    case A_TOKEN_LEFT_PARENTHESIS:
        return "(";
    case A_TOKEN_RIGHT_PARENTHESIS:
        return ")";
    case A_TOKEN_BITWISE_AND:
        return "&";
    case A_TOKEN_BITWISE_OR:
        return "|";
    case A_TOKEN_BITWISE_XOR:
        return "^";
    case A_TOKEN_AND:
        return "&&";
    case A_TOKEN_OR:
        return "||";
    case A_TOKEN_POWER_N:
        return "**";
    case A_TOKEN_NOT:
        return "!";
    case A_TOKEN_INVERT:
        return "~";
    case A_TOKEN_EOF:
        return "EOF";
    default:
        return "number";
    }
}
