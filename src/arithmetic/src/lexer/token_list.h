#ifndef LEXER_LIST_H
# define LEXER_LIST_H

#include "lexer.h"

struct arithmetic_token_list
{
    struct arithmetic_token *token;
    struct arithmetic_token_list *next;
};

struct arithmetic_lexer
{
    struct arithmetic_token_list *head;
    struct arithmetic_token_list *tail;
    size_t size;
};

#endif /* ! LEXER_LIST_H */
