/**
 * \file lexer.h
 * \brief file where we define function for the lexer
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date September 17th 2019
 *
 * Lexer.h where we define the function for the lexer
 *
 *
 */


#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token/token.h"

/**
 * \enum lexer_state
 * \brief enum contain state of lexer
 * 
 * Contain int that corresped to a state for the lexer
 *
 */
enum lexer_state
{
    STATE_NONE,                   //regular
    STATE_LEXING_QUOTES,          //in a '. asking for more input
    STATE_LEXING_DOUBLE_QUOTES,   //in a ". asking for more input
    STATE_UNFINISHED,             /*string could be parsed to a valid
                                  expression if given more characters*/
    STATE_FINISHED,               /*lexer successfully lexed string and
                                   parser returned a valid expression*/
    STATE_ERROR                   //lexer successfully lexed string
                                  //but parser returned an error
};


/**
 * \struct lexer
 * \brief Lexer object
 *
 * Lexer is an object that contain the state of the lexer (enum), 
 * a string (char *) and an iterator (size_t)
 *
 */
struct lexer
{
    //
    enum lexer_state state;
    // data
    char *str;
    size_t iterator;
};
/**
 * \struct token_array
 * \brief Token_array object 
 *
 * Token_array is an object that contain an array of token,
 * his capacity and his actual size
 *
 */

struct token_array
{
    struct token **tok_array;
    size_t capacity;
    size_t size;
};

//main lexing function
/**
 * \brief check the type of the token
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 *
 * \return token_type in the buffer, TOKEN_WORD if it is not a token valid
 *
 */
enum token_type token_check(char *str, size_t iterator, char *buffer);

/**
 * \brief create a new token
 * 
 * \param type type of new token
 * \param *value string of new token
 *
 * \return token , NULL if there is not enough memory
 */
struct token *token_init(enum token_type type, char *value);

/**
 * \brief free momory from token
 *
 * \param *token token that needs to be released
 *
 * \return Nothing
 */
void token_free(struct token *token);

/**
 *
 *
 */
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
