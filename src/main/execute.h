/**
 * \file execute.h
 * \brief functions necessary for execute comands
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 17th 2019
 *
 * Lexer.h where we define the function for the lexer
 *
 *
 */
#ifndef EXECUTE_H
#define EXECUTE_H

#include "42sh.h"
#include "readline.h"
/**
 * \brief handle the case wen the user hit ctrl + c
 *
 * \param int _ unused int
 *
 * \return void
 *
 */
void sigintHandler(int _);
/**
 * \brief execute command in the stdin
 *
 * \param struct execution_bundle *bundle bundle
 *
 * \return int the return of bash
 *
 */
int execute_stdin(struct execution_bundle *bundle);

/**
 * \brief execute command in the interactive mode
 *
 * \param struct execution_bundle *bundle bundle
 *
 * \return int the return of bash
 *
 */
int execute_interactive(struct execution_bundle *bundle);

/**
 * \brief execute command passed in arg
 *
 * \param struct execution_bundle *bundle bundle
 * \param char *cmd command to execute
 *
 * \return int the return of bash
 *
 */
int execute_cmd(struct execution_bundle *bundle, char *cmd);

/**
 * \brief execute command passed in arg
 *
 * \param struct execution_bundle *bundle bundle
 * \param char *script path of the script 
 *
 * \return int the return of bash
 *
 */
int execute_script(struct execution_bundle *bundle, char* script, int create);

#endif 
