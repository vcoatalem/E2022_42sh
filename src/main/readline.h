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
