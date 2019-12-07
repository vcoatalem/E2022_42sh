#ifndef ARITHMETIC_TOKEN_H
#define ARITHMETIC_TOKEN_H


/**
** \brief Type of a token (operators, value, ...)
*/
enum arithmetic_token_type
{
    A_TOKEN_PLUS = 0,
    A_TOKEN_MINUS,
    A_TOKEN_MULTIPLY,
    A_TOKEN_DIVIDE,
    A_TOKEN_LEFT_PARENTHESIS,
    A_TOKEN_RIGHT_PARENTHESIS,
    A_TOKEN_BITWISE_AND,
    A_TOKEN_BITWISE_OR,
    A_TOKEN_BITWISE_XOR,
    A_TOKEN_AND,
    A_TOKEN_OR,
    A_TOKEN_POWER_N,
    A_TOKEN_NOT,
    A_TOKEN_INVERT,
    A_TOKEN_EOF,
    A_TOKEN_NUMBER,
};

/**
** \brief Token struct declaration
*/
struct arithmetic_token
{
    /* type of the token */
    enum arithmetic_token_type type;
    /* hold the number (only used when type == TOKEN_NUMBER) */
    int value;
};

/**
** \brief String representation of a token (used for debugging and errors)
**
** \return a string describing the given token
** \param token to stringify
*/
const char *arithmetic_token_str(struct arithmetic_token *token);

/**
** \brief Token allocator and initialiser
**
** \return a pointer to the allocated token
*/
struct arithmetic_token *arithmetic_token_alloc(void);

/**
** \brief Wrapper to release memory of a token
**
** \param token the token to free
*/
void arithmetic_token_free(struct arithmetic_token *token);

char *a_token_str(enum arithmetic_token_type type);

#endif /* ! ARITHMETIC_TOKEN_H */
