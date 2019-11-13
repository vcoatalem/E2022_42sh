#include "token.h"

//TODO

//function wich allow us to return the good token_handler
token_handler token_to_handler(enum token_type type)
{
    switch (type)
    {
    case(TOKEN_IF):
        return ;
    default:
        return token_compare;
    }
}
