#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token/token.h"

struct token_array
{
    struct token **tok_array;
    size_t capacity;
    size_t size;
};

//main lexing function
enum token_type token_check(char *str, size_t iterator, char *buffer);

struct token *token_init(enum token_type type, char *value);
struct token_array *token_array_init();
void token_array_free(struct token_array *arr);
void token_array_add(struct token_array *arr, struct token *token);
void token_array_print(struct token_array *arr, FILE *out);

struct token_array *token_array_create(char *str);

#endif /* ! LEXER_H */
