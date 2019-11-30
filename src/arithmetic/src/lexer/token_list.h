#ifndef LEXER_LIST_H
# define LEXER_LIST_H

#include "lexer.h"

struct token_list
{
    struct token *token;
    struct token_list *next;
};

struct lexer
{
    struct token_list *head;
    struct token_list *tail;
    size_t size;
};

#endif /* ! LEXER_LIST_H */
