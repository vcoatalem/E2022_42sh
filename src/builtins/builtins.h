#ifndef BUILTINS_H
#define BUILTINS_H
#include "../main/42sh.h"

typedef int(*builtin_handler)(char **str, size_t size, struct execution_bundle *bundle);
builtin_handler str_to_builtin(char *name);
int builtin_history(char **str, size_t size, struct execution_bundle *bundle);

/**
 * \brief Execute the builtin shopt
 *
 * Builtin shopt, display 42sh option , has optional parameter ("-s", "-u", "-q")
 *
 * \param **str array of string 
 * \param size size of **str
 * \param *bundle 
 *
 * \return 0 , 1 if failed
 *
 */
int builtin_shopt(char **str, size_t size, struct execution_bundle *bundle);

#endif/* ( ! BUILTINS_H) */
