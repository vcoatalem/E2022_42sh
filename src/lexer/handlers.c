#include "lexer.h"

//Function which verify if buffer has the same type of argument type
int token_compare(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    if (str && iterator && 0)
        return 0;
    char *tmp = token_to_string(type);
    return (strcmp(buffer, tmp) == 0);
}

//Function for token which can be doubled (& | ; < >)
int token_single_char(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    if ((buffer[0] == '&' || buffer[0] == '|'
        || buffer[0] == ';' || buffer[0] == '<' || buffer[0] == '>')
        && buffer[1] == '\0')
    {
        if (buffer[0] == '>' && str[iterator] == '&')
            return 0;
        if (buffer[0] != str[iterator]
            && token_compare(str, iterator, buffer, type))
            return 1;
        return 0;
    }
    return 0;
}

//Function for token which is doubled (&& || ;; << >>)
int token_double_char(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    if ((buffer[0] == '&' || buffer[0] == '|'
        || buffer[0] == ';' || buffer[0] == '<' || buffer[0] == '>')
        && buffer[1] == buffer[0] && buffer[2] == '\0')
    {
        if (buffer[0] == '<' && buffer[1] == '<' && str[iterator] == '-')
            return 0;
        if (token_compare(str, iterator, buffer, type))
            return 1;
        return 0;
    }
    return 0;
}

//Function for token alone ('(' ')' '{' '}' ! '\n')
int token_one_char(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    if ((buffer[0] == '{' || buffer[0] == '}'
        || buffer[0] == '(' || buffer[0] == ')' || buffer[0] == '!'
        || buffer[0] == '\n'))
    {
        if (token_compare(str, iterator, buffer, type))
            return 1;
        return 0;
    }
    return 0;
}

//Function for token ("<<-" "<&" "<>" ">|" ">&" )
int token_diff_char(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    if ((buffer[0] == '<' && buffer[1] == '<' && buffer[2] == '-')
            || (buffer[0] == '<' && buffer[1] == '&')
            || (buffer[0] == '<' && buffer[1] == '>')
            || (buffer[0] == '>' && buffer[1] == '|')
            || (buffer[0] == '>' && buffer[1] == '&'))
    {
        return token_compare(str, iterator, buffer, type);
    }
    return 0;
}
//Function for token (stdin stdout stderr)
int token_terminal_char(char *str, size_t iterator, char *buffer,
        enum token_type type)
{
    if ((buffer[0] == '0' && (str[iterator] == '>' || str[iterator] == '<'))
        || (buffer[0] == '1' && (str[iterator] == '>' || str[iterator] == '<'))
        || (buffer[0] == '2' && (str[iterator] == '>' || str[iterator] == '<')))
    {
        return token_compare(str, iterator, buffer, type);
    }
    return 0;
}

int token_subshell(char *str, size_t iterator, char *buffer,
        enum token_type type)
{
    if (!type && !str && iterator == 0)
        return 0;
    if (strlen(buffer) > 3 && buffer[0] == '$' && buffer[1] == '('
        && buffer[2] != '(' && buffer[strlen(buffer) - 1] == ')')
        return token_compare(str, iterator, buffer, type);
    return 0;
}


int token_arithmetic(char *str, size_t iterator, char *buffer,
        enum token_type type)
{
    if (!type && !str && iterator == 0)
        return 0;
    if (strlen(buffer) > 3 && buffer[0] == '$' && buffer[1] == '('
        && buffer[2] == '(' && buffer[strlen(buffer) - 1] == ')')
        return 1;
    return 0;
}


//return token_type in buffer else return TOKEN_WORD if it's not a token
enum token_type token_check(char *str, size_t iterator, char *buffer)
{
    for (enum token_type i = TOKEN_EOL; i <= TOKEN_ARITHMETIC; ++i)
    {
        token_handler func = token_to_handler(i);
        if (func(str, iterator, buffer, i) == 1)
        {
            return i;
        }
    }
    return TOKEN_WORD;
}
