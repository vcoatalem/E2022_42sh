#ifndef TOKEN_H
#define TOKEN_H

/**
** \brief Type of a token (operators, value, ...)
*/

#include <stddef.h>

enum token_type
{
    TOKEN_WORD,
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
typedef int (*token_handler)(char *str, size_t iterator, char *buffer, enum
        token_type type);

int token_compare(char *str, size_t iterator, char *buffer, enum
        token_type type);


int token_single_char(char *str, size_t iterator, char *buffer, enum
        token_type type);


int token_double_char(char *str, size_t iterator, char *buffer, enum
        token_type type);

int token_one_char(char *str, size_t iterator, char *buffer, enum
        token_type type);

int token_diff_char(char *str, size_t iterator, char *buffer, enum
        token_type type);

int token_terminal_char(char *str, size_t iterator, char *buffer,
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
};

char *token_to_string(enum token_type type);
struct token *token_alloc(void);
void token_free(struct token *token);

#endif /* ! TOKEN_H */