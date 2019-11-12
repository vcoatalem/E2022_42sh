#include "token.h"

token_handler token_to_handler(token_type type)
{
    switch type
    {
    case(TOKEN_IF):
        return token_compare;

    }
}