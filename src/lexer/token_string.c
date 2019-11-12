#include "token.h"

#include <err.h>
#include <errno.h>

//TODO finish this function

char *token_to_string2(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_DO):
        return "do";
    case (TOKEN_DONE):
        return "done";
    case (TOKEN_CASE):
        return "case";
    case (TOKEN_ESAC):
        return "esac";
    case (TOKEN_FUNCTION):
        return "function";
    default:
        err(1, "Wrong type input\n");
        return "";
    }
}

char *token_to_string(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_IF):
        return "if";
    case (TOKEN_THEN):
        return "then";
    case (TOKEN_FI):
        return "fi";
    case (TOKEN_ELSE):
        return "else";
    case (TOKEN_ELIF):
        return "elif";
    case (TOKEN_WHILE):
        return "while";
    case (TOKEN_UNTIL):
        return "until";
    case (TOKEN_FOR):
        return "for";
    case (TOKEN_IN):
        return "in";
    default:
        return token_to_string2(type);
    }
}
