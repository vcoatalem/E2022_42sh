#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "readline.h"
//#include "execute.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../hashtable/hashtablevar.h"
#include "../hashtable/hashtablefunc.h"
#include "../options/options.h"

enum BASH_RETURN_VALUES
{
    BASH_RETURN_OK = 0,
    BASH_RETURN_ERROR = 1,
    BASH_RETURN_OPTIONS_ERROR = 2
};

struct execution_bundle
{
    struct options *options;
    struct grammar *grammar;
    struct hash_table_var *hash_table_var;
    struct hash_table_func *hash_table_func;

};

void appendhistory(char *cmd);

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
int execute_script(struct execution_bundle *bundle, char* script);



#endif /* BASH_H */
