#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

#define EXIT_NON_NUMERIC_ARGUMENT 128
#define EXIT_WRONG_ARGUMENT 2
#define EXIT_TOO_MANY_ARGUMENTS 1
#define EXIT_OK 0

int builtin_break(char **argv, size_t size, void *bundle_ptr)
{
    if (size > 2)
    {
        warnx("break: too many arguments");
        return EXIT_TOO_MANY_ARGUMENTS;
    }
    if (!bundle_ptr || (!argv && size))
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->ast_traversal_context.loop_depth == 0)
    {
        warnx("break: only meaningful in a `for', `while', or `until' loop");
        return EXIT_OK;
    }
    int val = 1;
    if (size == 2)
    {
        val = atoi(argv[1]);
        if (val == 0 && strcmp("0", argv[1]))
        {
            warnx("break: %s: numeric argument required", argv[1]);
            return EXIT_NON_NUMERIC_ARGUMENT;
        }
    }
    bundle->ast_traversal_context.found_break += val;
    return EXIT_OK;
}

int builtin_continue(char **argv, size_t size, void *bundle_ptr)
{
    if (size > 2)
    {
        warnx("continue: too many arguments");
        return EXIT_TOO_MANY_ARGUMENTS;
    }
    if (!bundle_ptr || (!argv && size))
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->ast_traversal_context.loop_depth == 0)
    {
        warnx("continue: only meaningful in a `for', `while', or `until' loop");
        return EXIT_OK;
    }
    int val = 1;
    if (size == 2)
    {
        val = atoi(argv[1]);
        if (val == 0 && strcmp("0", argv[1]))
        {
            warnx("continue: %s: numeric argument required", argv[1]);
            return EXIT_NON_NUMERIC_ARGUMENT;
        }
    }
    bundle->ast_traversal_context.found_continue += val;
    return EXIT_OK;
}

int builtin_exit(char **argv, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr)
        return -1;
    fprintf(stderr, "exit\n");
    int exit_val = size <= 1 ? 0 : atoi(argv[2]);
    if (size >= 2 && strcmp(argv[2], "0") != 0)
    {
        warnx("exit: %s: numeric argument expected", argv[1]);
        exit_val = EXIT_WRONG_ARGUMENT;
    }
    if (size > 2)
    {
        warnx("exit: %zu: too many arguments", size);
        exit_val = EXIT_TOO_MANY_ARGUMENTS;
    }
    exit(exit_val % 256);
}
