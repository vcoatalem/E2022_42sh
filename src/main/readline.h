/**
 * \file readline.h
 * \brief redefinition of function readline
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 17th 2019
 *
 * Lexer.h where we define the function for the lexer
 *
 *
 */

#ifndef READLINE_H
#define READLINE_H

/**
** \brief read input from standard input and display prompt if necessary
**
** The prompt is displayed after every new line if the standard input is a tty
**
** \return the next input line
** \param prompt the string to print as prompt
*/
char *get_next_line(const char *prompt);

#endif /* ! READLINE_H */
