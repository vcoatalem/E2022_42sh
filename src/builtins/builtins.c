#include "builtins.h"

#include <string.h>

builtin_handler str_to_builtin(char *name)
{
    if (!strcmp(name, "history"))
        return builtin_history;
    else if (!strcmp(name, "shopt"))
        return builtin_shopt;
    else if (!strcmp(name, "cd"))
        return builtin_cd;
    return NULL;
}
