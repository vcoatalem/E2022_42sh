#ifndef TOKEN_H
#define TOKEN_H

/**
** \brief Type of a token (operators, value, ...)
*/
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
typedef (int)(*token_handler)(char *str, size_t iterator, char *buffer, enum
        token_type type);


/**
** \brief Token struct declaration
*/
struct token
{
    /* type of the token */
    enum token_type type;
    char *value;
};

/**
** \brief String representation of a token (used for debugging and errors)
**
** \return a string describing the given token
** \param token to stringify
*/
const char *token_str(struct token *token);

/**
** \brief Token allocator and initialiser
**
** \return a pointer to the allocated token
*/
struct token *token_alloc(void);

/**
** \brief Wrapper to release memory of a token
**
** \param token the token to free
*/
void token_free(struct token *token);

#endif /* ! TOKEN_H */
