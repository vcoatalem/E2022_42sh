#ifndef BUILTINS_H
#define BUILTINS_H
#include "../main/42sh.h"

typedef int(*builtin_handler)(char **str, size_t size, struct execution_bundle *bundle);
builtin_handler str_to_builtin(char *name);
int builtin_history(char **str, size_t size, struct execution_bundle *bundle);


#endif/* ( ! BUILTINS_H) */
