#include <stddef.h>
#include <stdio.h>

#include "builtins.h"
#include "../main/42sh.h"

static char *escaped_sequence(char *s, size_t index)
{
    char *c = calloc(1, sizeof(char));

    if (s[index] == '\\')
        c[0] = '\\';
    else if (s[index] == 'a')
        c[0] = '\a';
    else if (s[index] == 'b')
        c[0] = '\b';
    else if (s[index] == 'e')
        c[0] = 27;
    else if (s[index] == 'f')
        c[0] = '\f';
    else if (s[index] == 'n')
        c[0] = '\n';
    else if (s[index] == 'r')
        c[0] = '\r';
    else if (s[index] == 't')
        c[0] = '\t';
    else if (s[index] == 'v')
        c[0] = '\v';
    else if (s[index] == '0')
    {
    }
    else if (s[index] == 'x')
    {
    }

    return c;
}

static void _printf_escaped(char *s)
{
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i + 1] != '\0' && s[i] == '\\')
        {
            i++;
            if (s[i] == 'c')
                break;

            printf("%s", escaped_sequence(s, i));
        }

        else
            printf("%c", s[i]);
    }
}

int builtin_echo(char **argv, size_t size, void *bundle_ptr)
{
    if (bundle_ptr == NULL)
        return 1;

    int trailing_newline_set =  0;
    int enable_backslash_set = 0;
    int disable_backslash_set = 1;

    if (size >= 2)
    {
        size_t i = 0;
        while (++i < size && argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == 'n')
                    trailing_newline_set = 1;

                if (argv[i][j] == 'e')
                {
                    enable_backslash_set = 1;
                    disable_backslash_set = 0;
                }

                if (argv[i][j] == 'E')
                {
                    disable_backslash_set = 1;
                    enable_backslash_set = 0;
                }
            }
        }

        if (enable_backslash_set == 1)
        {
            for (; i < size - 1; i++)
            {
                _printf_escaped(argv[i]);
                printf(" ");
            }
            _printf_escaped(argv[i]);
        }

        if (disable_backslash_set == 1)
        {
            for (; i < size - 1; i++)
                printf("%s " , argv[i]);
            printf("%s", argv[i]);
        }

        if (trailing_newline_set == 0)
            printf("\n");

    }

    return 0;
}
