#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "readline.h"
#include "../builtins/builtins.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../hashtable/hashtablevar.h"
#include "../hashtable/hashtablefunc.h"
#include "../options/options.h"

#define BASH_RETURN_OK 0
#define BASH_RETURN_ERROR 2

struct execution_bundle
{
    struct options *options;
    struct hash_table_var *hash_table_var;
    struct hash_table_func *hash_table_func; 
    struct shopt *shopt;
    struct analysis_table *parser_table;
    struct lexer *lexer;
    struct parser *parser;
    struct ast *ast;
    struct token_array *token_array;
    struct ast_traversal_context ast_traversal_context;
};
void init_history(struct execution_bundle *bundle);

void appendhistory(char *cmd, struct execution_bundle *bundle);

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
 U* \return int the return of bash
 R*
 */
int execute_script(struct execution_bundle *bundle, char* script);


// ADVANCED PROMPT

/**
 * \brief compare which type of variable it is
 *
 * \param char *var
 * \param size_t *index
 *
 * \return char * output corresponding to var
 */
char *case_var(char *var, size_t *index);

/**
 * \brief replace all variable in prompt
 *
 * \param char *prompt
 *
 * \return char * replaced prompt
 */
char *replace_prompt(char *prompt);

#endif /* BASH_H */
