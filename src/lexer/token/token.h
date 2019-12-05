/**
 * \file token.h
 * \brief file where we define function for the token
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date September 17th 2019
 *
 * token.h where we define the function for the lexer
 *
 *
 */


#ifndef TOKEN_H
#define TOKEN_H

/**
** \brief Type of a token (operators, value, ...)
*/

#include <stddef.h>

#define NB_TOKENS 47

/**
 * \enum token_type
 * \brief enum contain all type of token
 *
 * Contain int that correspond to a type of token
 *
 */
enum token_type
{
    TOKEN_WORD,
    TOKEN_ASSIGNMENT,
    TOKEN_FUNCDEC, //TODO: lex this ( foo(), bar(), ...)
    TOKEN_SUBSHELL,
    TOKEN_ARITHMETIC,
    TOKEN_WORD_EXPAND,
    TOKEN_WORD_TILDE, //TODO: lex this ( ~, ~-, ~/ ...)
    TOKEN_WORD_NO_SUBSTITUTION,
    TOKEN_EOF,
    TOKEN_EOL,
    TOKEN_SEMI_COLON,
    TOKEN_DOUBLE_SEMICOLON,
    TOKEN_AMPERSAND,
    TOKEN_DOUBLE_AMPERSAND,
    TOKEN_PIPE,
    TOKEN_DOUBLE_PIPE,
    TOKEN_EXCLAMATION_POINT,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_LESS,
    TOKEN_GREAT,
    TOKEN_DOUBLE_LESS,
    TOKEN_DOUBLE_GREAT,
    TOKEN_DOUBLE_LESS_DASH,
    TOKEN_LESS_AMPERSAND,
    TOKEN_GREAT_AMPERSAND,
    TOKEN_GREAT_PIPE,
    TOKEN_LESS_GREAT,
    TOKEN_STDIN,
    TOKEN_STDOUT,
    TOKEN_STDERR,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_WHILE,
    TOKEN_UNTIL,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_CASE,
    TOKEN_ESAC,
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_FI,
    TOKEN_ELSE,
    TOKEN_ELIF,
    TOKEN_FUNCTION,
};


// retrun 1 if the string has a token that we recognize else return 0

/**
 * \brief handler for make compare if it is the good token
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
typedef int (*token_handler)(char *str, size_t iterator, char *buffer, enum
        token_type type);

/**
 * \brief verify if buffer has the same type of argument type
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_compare(char *str, size_t iterator, char *buffer, enum
        token_type type);


/**
 * \brief For token which can be doubled (& | ; < >)
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_single_char(char *str, size_t iterator, char *buffer, enum
        token_type type);


/**
 * \brief For token which is doubled (&& || ;; << >>)
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_double_char(char *str, size_t iterator, char *buffer, enum
        token_type type);

/**
 * \brief Function for token alone ('(' ')' '{' '}' ! '\n')
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_one_char(char *str, size_t iterator, char *buffer, enum
        token_type type);
/**
 * \brief Function for token ("<<-" "<&" "<>" ">|" ">&" )
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_diff_char(char *str, size_t iterator, char *buffer, enum
        token_type type);
/**
 * \brief Function for token (stdin stdout stderr)
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_terminal_char(char *str, size_t iterator, char *buffer,
        enum token_type type);

/**
 * \brief Function for token ( "$( blabla )")
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_subshell(char *str, size_t iterator, char *buffer,
        enum token_type type);

/**
 * \brief Function for token ("$(( blabla ))")
 *
 * \param *str string in the input,
 * \param iterator where the program is in the string
 * \param *buffer buffer where tokens are stocked
 * \param *token_type type token_type to compare
 *
 * \return int 1->true 0->false
 *
 */
int token_arithmetic(char *str, size_t iterator, char *buffer,
        enum token_type type);

token_handler token_to_handler(enum token_type type);


/**
** \brief Token struct declaration
*/
struct token
{
    /* type of the token */
    enum token_type type;
    char *value;
    int quoted;
};

/**
 * \brief Convert a token into a string
 *
 * \param enum token_type type type of token
 *
 * \return char* string of the token, default case return: word
 *
 */
char *token_to_string(enum token_type type);

/**
 * \brief Convert a token into a displayable string
 *
 * \param enum token_type type type of token
 *
 * \return "\\n" when TOKEN_EOL, token_to_string(type) otherwise
 *
 */
char *token_to_formatted_string(enum token_type type);

/**
 * \brief Print string value of a token
 *
 * \param enum token_type type type of token
 *
 * \prints token_to_string(type), or '\n' if type is TOKEN_EOL
 *
 */
void token_print(enum token_type type);

struct token *token_alloc(void);
void token_free(struct token *token);

#endif /* ! TOKEN_H */
