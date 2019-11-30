#include "parser.h"

int token_type_is_value(enum token_type type)
{
    return type == TOKEN_WORD || type == TOKEN_WORD_W_STAR
        || type == TOKEN_SUBSHELL || type == TOKEN_ARITHMETIC
        || type == TOKEN_LESS || type == TOKEN_GREAT
        || type == TOKEN_DOUBLE_GREAT || type == TOKEN_GREAT_AMPERSAND
        || type == TOKEN_DOUBLE_LESS || type == TOKEN_GREAT_PIPE
        || type == TOKEN_LESS_GREAT
        || type == TOKEN_STDIN || type == TOKEN_STDOUT || type == TOKEN_STDERR
        || type == TOKEN_ASSIGNMENT //keywords values handling below
        || type == TOKEN_IF || type == TOKEN_ELSE || type == TOKEN_ELIF
        || type == TOKEN_DO || type == TOKEN_DONE || type == TOKEN_CASE
        || type == TOKEN_ESAC || type == TOKEN_EXCLAMATION_POINT
        || type == TOKEN_WHILE || type == TOKEN_UNTIL;
}
