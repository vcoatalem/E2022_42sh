#include "builtins.h"

#include <string.h>

builtin_handler str_to_builtin(char *name)
{
    if (!name)
        return NULL;
    if (!strcmp(name, "history"))
        return builtin_history;
    else if (!strcmp(name, "shopt"))
        return builtin_shopt;
    else if (!strcmp(name, "cd"))
        return builtin_cd;
    else if (!strcmp(name, "export"))
        return builtin_export;
    else if (!strcmp(name, "break"))
        return builtin_break;
    else if (!strcmp(name, "continue"))
        return builtin_continue;
    else if (!strcmp(name, "exit"))
        return builtin_exit;
    else if (!strcmp(name, "alias"))
        return builtin_alias;
    else if (!strcmp(name, "unalias"))
        return builtin_unalias;
    else if (!strcmp(name, "echo"))
        return builtin_echo;
    else if (!strcmp(name, ".") || !strcmp(name, "source"))
        return builtin_source;
    return NULL;
}
