#include <errno.h>
#include <err.h>

#include "lexer.h"
#include "token/token.h"

//function wich allow us to return the good token_handler


token_handler token_to_handler5(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_STDIN):
        return token_terminal_char;
    case (TOKEN_STDOUT):
        return token_terminal_char;
    case (TOKEN_STDERR):
        return token_terminal_char;
    default:
        warn("wrong token type");
        return NULL;
    }
}


token_handler token_to_handler4(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_LESS):
        return token_single_char;
    case (TOKEN_GREAT):
        return token_single_char;
    case (TOKEN_DOUBLE_LESS):
        return token_double_char;
    case (TOKEN_DOUBLE_GREAT):
        return token_double_char;
    case (TOKEN_DOUBLE_LESS_DASH):
        return token_diff_char;//TODO NOT SURE
    case (TOKEN_LESS_AMPERSAND):
        return token_diff_char;
    case (TOKEN_GREAT_AMPERSAND):
        return token_diff_char;
    case (TOKEN_GREAT_PIPE):
        return token_diff_char;
    case (TOKEN_LESS_GREAT):
        return token_diff_char;
    default:
        return token_to_handler5(type);
    }
}



token_handler token_to_handler3(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_AMPERSAND):
        return token_single_char;
    case (TOKEN_DOUBLE_AMPERSAND):
        return token_double_char;
    case (TOKEN_PIPE):
        return token_single_char;
    case (TOKEN_DOUBLE_PIPE):
        return token_double_char;
    case (TOKEN_EXCLAMATION_POINT):
        return token_one_char;
    case (TOKEN_LEFT_BRACKET):
        return token_one_char;
    case (TOKEN_RIGHT_BRACKET):
        return token_one_char;
    case (TOKEN_LEFT_PARENTHESIS):
        return token_one_char;
    case (TOKEN_RIGHT_PARENTHESIS):
        return token_one_char;
    default:
        return token_to_handler4(type);
    }
}



token_handler token_to_handler2(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_DO):
        return token_compare;
    case (TOKEN_DONE):
        return token_compare;
    case (TOKEN_CASE):
        return token_compare;
    case (TOKEN_ESAC):
        return token_compare;
    case (TOKEN_FUNCTION):
        return token_compare;
    /*case (TOKEN_EOF):
   f     err(1, "error type EOF");*/
    case (TOKEN_EOL):
        return token_one_char;
    case (TOKEN_SEMI_COLON):
        return token_single_char;
    case (TOKEN_DOUBLE_SEMICOLON):
        return token_double_char;
    default:
        return token_to_handler3(type);
    }
}

token_handler token_to_handler(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_IF):
        return token_compare;
    case (TOKEN_THEN):
        return token_compare;
    case (TOKEN_FI):
        return token_compare;
    case (TOKEN_ELSE):
        return token_compare;
    case (TOKEN_ELIF):
        return token_compare;
    case (TOKEN_WHILE):
        return token_compare;
    case (TOKEN_UNTIL):
        return token_compare;
    case (TOKEN_FOR):
        return token_compare;
    case (TOKEN_IN):
        return token_compare;
    default:
        return token_to_handler2(type);
    }
}
