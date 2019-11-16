#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token/token.h"

enum lexer_state
{
    STATE_NONE,                   //regular
    STATE_LEXING_QUOTES,          //in a '. asking for more input
    STATE_LEXING_DOUBLE_QUOTES,   //in a ". asking for more input
    STATE_UNFINISHED,             //string could be parsed to a valid expression if given more characters
    STATE_FINISHED,               //lexer successfully lexed string and parser returned a valid expression
    STATE_ERROR                   //lexer successfully lexed string but parser returned an error
};

struct lexer
{
    //
    enum lexer_state state;
    // data
    char *str;
    size_t iterator;
};


struct token_array
{
    struct token **tok_array;
    size_t capacity;
    size_t size;
};

//main lexing function
enum token_type token_check(char *str, size_t iterator, char *buffer);

struct token *token_init(enum token_type type, char *value);
void token_free(struct token *token);
struct token_array *token_array_init();
void token_array_free(struct token_array *arr);
void token_array_add(struct token_array *arr, struct token *token);

void token_arrays_fusion(struct token_array *arr1, struct token_array *arr2);


void token_array_print(struct token_array *arr, FILE *out);

int is_separator(char c);

int is_space(char c);

void handle_separators(char *str, size_t *iterator, char *buffer,
        size_t *index, struct token_array *arr);

//TODO: lexer basic init
struct lexer *lexer_init(void);

//TODO: fill lexer with strings (concat)
void lexer_add_string(struct lexer *lexer, char *str);

//TODO: empty lexer
void lexer_clear(struct lexer *lexer);

//TODO: turn token_array_create into lex
struct token_array *token_array_create(char *str);
struct token_array *lex(struct lexer *lexer);





#endif /* ! LEXER_H */
