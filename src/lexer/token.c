#include "lexer/token.h"
#include "utils/xalloc.h"

#include <stdio.h>
#include <stdlib.h>

const char *token_str(struct token *token)
{
    static const char *token_strs[] = { "+", "-", "*", "/", "(", ")", "EOF" };
    static char number_str[11];

    if (token->type != F_NUMBER)
        return token_strs[token->type];

    sprintf(number_str, "%d", token->value);
    return number_str;
}

struct token *token_alloc(void)
{
    struct token *res = xmalloc(sizeof(*res));
    res->type = F_EOF;
    res->value = 0;

    return res;
}

void token_free(struct token *token)
{
    free(token);
}


typedef (int)(*token_handler)(char *str, size_t iterator, char *buffer, enum
        token_type type)

token_handler token_compare(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    (void *) str;
    (void *) iterator;
    return strcmp(buffer, token_to_string(type)) == 0;
}
//Function for token which can be doubled (& | ; < >)
token_handler token_single_char(char *str, size_t iterator, char *buffer, enum
        token_type type)
{
    (void *) str;

    if ((buffer[0] == '&' || buffer[0] == '|' 
        || buffer[0] == ';' || buffer[0] == '<' || buffer[0] == '>')
        && buffer[1] == 0)
    {
        if (buffer[0] != str[iterator + 1]
            && token_compare(str, iterator, buffer, type))
            return 1;
        return 0;
    }
    return 0;
}


token_type checktoken(char *str, size_t iterator, char *buffer)
{
    for (enum token_type i = TOKEN_EOL; i <= TOKEN_FUNCTION; ++i)
    {
        token_handler func = token_to_handler(i);
        if (func(str, iterator, buffer, i) == 1)
        {
            return i;
        }
    }
    return TOKEN_WORD;
}

int 
{
    size_t index = 0;
    while (str[iterator] != 0)
    {
        buffer[index] = str[iterator];
        index++;
        iterator++;
        buffer[index] = '\0';
        checktoken()
    }

    return (*token_compare[type](*buffer));
}
