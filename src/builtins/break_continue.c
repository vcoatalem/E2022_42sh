#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

int builtin_break(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || (!str && size))
        return 1;
    printf("entered break\n");
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->ast_traversal_context.loop_depth == 0)
    {
        warnx("break: only meaningful in a `for', `while', or `until' loop");
        return 0;
    }
    bundle->ast_traversal_context.found_break = 1;
    return 0;
}

int builtin_continue(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || (!str && size))
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->ast_traversal_context.loop_depth == 0)
    {
        warnx("continue: only meaningful in a `for', `while', or `until' loop");
        return 0;
    }
    bundle->ast_traversal_context.found_continue = 1;
    return 0;
}
