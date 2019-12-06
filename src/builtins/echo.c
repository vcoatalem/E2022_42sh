#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"
#include "../main/42sh.h"

struct flags
{
    int trailing_newline_set;
    int enable_backslash_set;
    int disable_backslash_set;

};

static struct flags *flags_init(void)
{
    struct flags *f = calloc(1, sizeof(struct flags));
    f->trailing_newline_set = 0;
    f->enable_backslash_set = 0;
    f->disable_backslash_set = 1;

    return f;
}

static void flags_reset(struct flags *f)
{
    f->trailing_newline_set = 0;
    f->enable_backslash_set = 0;
    f->disable_backslash_set = 1;
}

static void set_newline(struct flags *f)
{
    f->trailing_newline_set = 1;
}

static void set_enable_backslash(struct flags *f)
{
    f->enable_backslash_set = 1;
    f->disable_backslash_set = 0;
}

static void set_disable_backslash(struct flags *f)
{
    f->enable_backslash_set = 0;
    f->disable_backslash_set = 1;
}

static char *escaped_sequence(char *s, size_t *index)
{
    char *c = calloc(1, sizeof(char));

    if (s[*index] == '\\')
        c[0] = '\\';
    else if (s[*index] == 'a')
        c[0] = '\a';
    else if (s[*index] == 'b')
        c[0] = '\b';
    else if (s[*index] == 'e')
        c[0] = 27;
    else if (s[*index] == 'f')
        c[0] = '\f';
    else if (s[*index] == 'n')
        c[0] = '\n';
    else if (s[*index] == 'r')
        c[0] = '\r';
    else if (s[*index] == 't')
        c[0] = '\t';
    else if (s[*index] == 'v')
        c[0] = '\v';
    else if (s[*index] == '0')
    {
        char *end;
        c[0] = strtol(s + (*index) + 1, &end, 8);
        (*index) += end - (s + (*index) + 1);
    }
    else if (s[*index] == 'x')
    {
        char tmp[3] =
        {
            s[(*index) + 1], s[(*index) + 2], 0
        };
        char *end;
        c[0] = strtol(tmp, &end, 16);
        (*index) += end - tmp;
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

            printf("%s", escaped_sequence(s, &i));
        }

        else
            printf("%c", s[i]);
    }
}

static void _print(char **argv, size_t size, size_t index, struct flags *f)
{
    if (f->enable_backslash_set == 1)
    {
        for (; index < size - 1; index++)
        {
            _printf_escaped(argv[index]);
            printf(" ");
        }
        _printf_escaped(argv[index]);
    }

    if (f->disable_backslash_set == 1)
    {
        for (; index < size - 1; index++)
            printf("%s " , argv[index]);
        printf("%s", argv[index]);
    }

    if (f->trailing_newline_set == 0)
        printf("\n");
}

int builtin_echo(char **argv, size_t size, void *bundle_ptr)
{
    if (bundle_ptr == NULL)
        return 1;

    struct flags *f = flags_init();
    if (size >= 2)
    {
        size_t i = 0;
        while (++i < size && argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == 'n')
                    set_newline(f);

                else if (argv[i][j] == 'e')
                    set_enable_backslash(f);

                else if (argv[i][j] == 'E')
                    set_disable_backslash(f);

                else
                {
                    flags_reset(f);
                    printf("%s ", argv[i]);
                    break;
                }
            }
        }

        _print(argv, size, i, f);
    }

    free(f);
    return 0;
}
