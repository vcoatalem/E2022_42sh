#include "token.h"

//TODO finish this function
char *token_to_string(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_IF):
        return "if";
    case (TOKEN_THEN):
        return "then";
    default:
        return "error";
    }
}