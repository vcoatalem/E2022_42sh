/**
 * \file lexer.h
 * \brief file where we define function for the lexer
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 17th 2019
 *
 * File where we define the function for the lexer
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
 * Contain int that corresponded to a state for the lexer
 *
 *
 */
enum lexer_state
{
    LEXER_STATE_NONE,                   //regular
    LEXER_STATE_LEXING_QUOTES,          //in a '. asking for more input
    LEXER_STATE_LEXING_DOUBLE_QUOTES,   //in a ". asking for more input
    LEXER_STATE_LEXING_SLASH,
    LEXER_STATE_UNFINISHED,             /*string could be parsed to a valid
                                          expression if given more characters*/
    LEXER_STATE_SUBSHELL_DOL,
    LEXER_STATE_SUBSHELL_QUOTE,
    LEXER_STATE_FINISH_LEXING_WORD,

    LEXER_STATE_FINISHED,               /*lexer successfully lexed string and
                                          parser returned a valid expression*/
    LEXER_STATE_ERROR                   //lexer successfully lexed string
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
 * \brief check token type
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
 * \return None
 */
void token_free(struct token *token);

/**
 * \brief  create an object token_array
 *
 *allocate memory for an object token_array and create an object token_array
 *
 * \return *token_array a new array of token
 */
struct token_array *token_array_init();

/**
 * \brief free a token_array
 *
 * free a token_array
 *
 * \param *arr token_array that needs to be released
 *
 */
void token_array_free(struct token_array *arr);

/**
 *\brief add a token in token_array
 *
 * add a new token in token_array.
 * grow size of token_array.
 * grow the capacity of token_array if size equals capacity
 *
 * \param *arr the token_array where we add the new token
 * \param *token the token that will be added to the token_array
 *
 * \return None
 */
void token_array_add(struct token_array *arr, struct token *token);

/**
 * \brief concatenate the *arr1 with *arr2
 *
 * Useful when we are in interactive mode and we want to fusionate two arrays
 * We have to stick the last token of the first array with the first token
 * of the second array with a \n between them.
 *
 * \param *arr1 the token_array that was already completed
 * \param *arr2 the token_array that has been filled
 *
 * \return None
 */
void token_arrays_fusion(struct token_array *arr1, struct token_array *arr2);

/**
 * \brief print token_array
 *
 * print the token_array that is in parameter to the FILE *out
 *
 * \param *arr token_array which will be print
 * \param *out FILE where the token_array will be print
 *
 * \return None
 */
void token_array_print(struct token_array *arr, FILE *out);

/**
 *\brief check if the character is a separator
 *
 * check if the character c is a separator (' ', '(', ')', '|', '&', '\t', ';',
 * '\0', '>', '<')
 *
 * \param c char that the function check
 *
 * \return 1 if it is a separator, 0 if ot is not
 */
int is_separator(char c);


/**
 * \brief check if the character is a space
 *
 * check if the character c is a ' ' or '\t'
 *
 * \param c char that the function check
 *
 * \return 1 if it is ' ' or '\t', 0 if it is not
 */
int is_space(char c);

void check_assignment(char *buffer, struct token_array *arr, int is_string);


/**
 * \brief handle character which is a separator
 *
 *
 *
 */
void handle_separators(char *str, size_t *iterator, char *buffer,
        size_t *index, struct token_array *arr, int is_string);

/**
 * \brief create a new lexer object
 *
 * create a new lexer object and allocate memory for this object.
 * set state to NONE, *str to NULL, iterator to 0
 *
 * \param None
 *
 * \return lexer the new_lexer
 */
struct lexer *lexer_init(void);

/**
 * \brief add a string in the lexer object
 *
 * add string in argument  in the lexer string
 * concatenate the string in the lexer object with the new one
 *
 * \param *lexer lexer object
 * \param *str string that the function will add to the string in lexer
 *
 * \return None
 */
void lexer_add_string(struct lexer *lexer, char *str);

/**
 * \brief free lexer
 *
 * free the string in lexer object and then the lexer
 *
 * \param *lexer lexer which will be released
 *
 * \return None
 */
void lexer_clear(struct lexer *lexer);


void lexer_free(struct lexer *lexer);

//TODO: turn token_array_create into lex
struct token_array *token_array_create(char *str);


/**
 * \brief fill a token_array object
 *
 * with the string in the lexer object create a token_array object
 * and fill it with tokens find in the string
 *
 *
 * \param *lexer lexer with a string which does not have a token_array
 * associated
 *
 * \return *token_array token_array of the lexer's string
 */
struct token_array *lex(struct lexer *lexer);

#endif /* ! LEXER_H */
