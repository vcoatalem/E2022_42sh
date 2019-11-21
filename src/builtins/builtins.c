#include "builtins.h"

builtin_handler str_to_builtin(char *name)
{
    if (strcmp(name, "history"))
        return builtin_history;
    /*else if (strcmp(name, "shopt"))
        return builtin_shopt;*/
    return NULL;
}
