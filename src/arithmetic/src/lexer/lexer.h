#ifndef LEXER_H
#define LEXER_H

#include "lexer/token.h"

/**
** \brief This is your struct lexer forward declaration.
**
** You should not edit this struct declaration but define one with the
** same name in another header file.
*/
struct arithmetic_lexer;

/**
** \brief Lexer allocator and initialiser
** \param str the string to use as input stream.
*/
struct arithmetic_lexer *arithmetic_lexer_alloc(const char *str);

/**
** \brief Wrapper to release every resources still held in a lexer.
**
** \param lexer the lexer to free
*/
void arithmetic_lexer_free(struct arithmetic_lexer *lexer);

/**
** \brief Return the first token from the input stream without consuming it.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct arithmetic_token *arithmetic_lexer_peek(struct arithmetic_lexer *lexer);

/** 
** \brief Return and consume the next token from the input stream.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct arithmetic_token *arithmetic_lexer_pop(struct arithmetic_lexer *lexer);

#endif /* ! ARITHMETIC_LEXER_H */
