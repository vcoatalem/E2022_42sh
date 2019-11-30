#ifndef LEXER_H
#define LEXER_H

#include "lexer/token.h"

/**
** \brief This is your struct lexer forward declaration.
**
** You should not edit this struct declaration but define one with the
** same name in another header file.
*/
struct lexer;

/**
** \brief Lexer allocator and initialiser
** \param str the string to use as input stream.
*/
struct lexer *lexer_alloc(const char *str);

/**
** \brief Wrapper to release every resources still held in a lexer.
**
** \param lexer the lexer to free
*/
void lexer_free(struct lexer *lexer);

/**
** \brief Return the first token from the input stream without consuming it.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct token *lexer_peek(struct lexer *lexer);

/** 
** \brief Return and consume the next token from the input stream.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct token *lexer_pop(struct lexer *lexer);

#endif /* ! LEXER_H */
