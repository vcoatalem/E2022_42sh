#include "token.h"

#include <err.h>
#include <errno.h>

char *token_to_string5(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_STDIN):
        return "0";
    case (TOKEN_STDOUT):
        return "1";
    case (TOKEN_STDERR):
        return "2";
    case (TOKEN_ASSIGNMENT):
        return "word_assignment";
    case (TOKEN_FUNCDEC):
        return "function_declaration";
    case (TOKEN_WORD_EXPAND):
        return "word_expand";
    case (TOKEN_SUBSHELL):
        return "subshell";
    case (TOKEN_ARITHMETIC):
        return "arithmetic";
    case (TOKEN_WORD_NO_SUBSTITUTION):
        return "No Substitution";
    case(TOKEN_WORD_TILDE):
        return "word tilde";
    default:
        return "word";
    }
}

char *token_to_string4(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_LESS):
        return "<";
    case (TOKEN_GREAT):
        return ">";
    case (TOKEN_DOUBLE_LESS):
        return "<<";
    case (TOKEN_DOUBLE_GREAT):
        return ">>";
    case (TOKEN_DOUBLE_LESS_DASH):
        return "<<-";
    case (TOKEN_LESS_AMPERSAND):
        return "<&";
    case (TOKEN_GREAT_AMPERSAND):
        return ">&";
    case (TOKEN_GREAT_PIPE):
        return ">|";
    case (TOKEN_LESS_GREAT):
        return "<>";
    default:
        return token_to_string5(type);
    }
}

char *token_to_string3(enum token_type type)
{
    switch (type)
    {
    case (TOKEN_AMPERSAND):
        return "&";
    case (TOKEN_DOUBLE_AMPERSAND):
        return "&&";
    case (TOKEN_PIPE):
        return "|";
    case (TOKEN_DOUBLE_PIPE):
        return "||";
    case (TOKEN_EXCLAMATION_POINT):
        return "!";
    case (TOKEN_LEFT_BRACKET):
        return "{";
    case (TOKEN_RIGHT_BRACKET):
        return "}";
    case (TOKEN_LEFT_PARENTHESIS):
        return "(";
    case (TOKEN_RIGHT_PARENTHESIS):
        return ")";
    default:
        return token_to_string4(type);
    }
}

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
    case (TOKEN_EOF):
        return "\0";
    case (TOKEN_EOL):
        return "\n";
    case (TOKEN_SEMI_COLON):
        return ";";
    case (TOKEN_DOUBLE_SEMICOLON):
        return ";;";
    default:
        return token_to_string3(type);
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

char *token_to_formatted_string(enum token_type type)
{
    if (type == TOKEN_EOF)
    {
        return "EOF";
    }
    if (type == TOKEN_EOL)
    {
        return "\\n";
    }
    else
        return token_to_string(type);
}
