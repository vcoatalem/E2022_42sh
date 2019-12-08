#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

int builtin_source(char **argv, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || !argv)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        printf("Source need args\n");
        return 2;
    }
    if (size > 2)
        bundle->options->begargs = 2;
    bundle->options->args = argv;
    int result = execute_script(bundle, argv[1]);
    bundle->lexer = lexer_init(bundle->hash_table_aliases);
    return result;
}
