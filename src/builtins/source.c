#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

int builtin_source(char **argv, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        return 2;
    }
    return execute_script(bundle, argv[1]);
}
