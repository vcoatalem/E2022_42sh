#include "parser.h"

int token_type_is_value(enum token_type type)
{
    return type == TOKEN_WORD || type == TOKEN_LESS || type == TOKEN_GREAT
        || type == TOKEN_DOUBLE_GREAT || type == TOKEN_GREAT_AMPERSAND
        || type == TOKEN_DOUBLE_LESS || type == TOKEN_GREAT_PIPE
        || type == TOKEN_LESS_GREAT
        || type == TOKEN_STDIN || type == TOKEN_STDOUT || type == TOKEN_STDERR
        || type == TOKEN_ASSIGNMENT;
}
