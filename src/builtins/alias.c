#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

int builtin_alias(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || !str)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size >= 2 && strcmp(str[1], "-p") == 0)
    {
        return 1;
    }
    return 1;
}
