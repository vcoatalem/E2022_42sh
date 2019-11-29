#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "42sh.h"

static char *case_a()
{
    char *result = calloc(2, sizeof(char));
    result[0] = '\a';
    return result;
}

static char *case_d()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char *result = calloc(1024, sizeof(char));
    size_t nb = strftime(result, 1024, "%A %B %d", tm);
    result = realloc(result, nb * sizeof(char) + 1);
    result[nb] = '\0';

    return result;
}

// TODO
static char *get_format(char *var, size_t *index)
{
    if (!var && index)
        return NULL;

    return NULL;
}

static char *case_D(char *format)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char *result = calloc(1024, sizeof(char));
    size_t nb = strftime(result, 1024, format, tm);
    result = realloc(result, nb * sizeof(char) + 1);
    result[nb] = '\0';

    return result;
}

static char *case_e()
{
    char *result = calloc(2, sizeof(char));
    result[0] = 27;
    return result;
}

// TODO
static char *case_h()
{
    return NULL;
}

// TODO
static char *case_H()
{
    return NULL;
}

static char *case_n()
{
    char *result = calloc(2, sizeof(char));
    result[0] = '\n';
    return result;
}

static char *case_r()
{
    char *result = calloc(2, sizeof(char));
    result[0] = '\r';
    return result;
}

// TODO
static char *case_s()
{
    return NULL;
}

// TODO
static char *case_u()
{
    return NULL;
}

// TODO
static char *case_w()
{
    return NULL;
}

// TODO
static char *case_W()
{
    return NULL;
}

// TODO
static char *case_dollar_sign()
{
    return NULL;
}

static char *case_nnn()
{
    char *result = calloc(2, sizeof(char));
    result[0] = ' ';
    return result;
}

static char *case_backslash()
{
    char *result = calloc(2, sizeof(char));
    result[0] = '\\';
    return result;
}

// TODO
static char *case_open_bracket()
{
    return NULL;
}

char *replace_prompt_var(char *var, size_t *index)
{
    // ASCII bell character
    if (var[*index] == 'a')
        return case_a();

    // Date in 'weekday month day' format (e.g. Friday November 29)
    else if (var[*index] == 'd')
        return case_d();

    // D{format}: format is passed to strftime and result is inserted
    //              into prompt
    else if (var[*index] == 'D')
        return case_D(get_format(var, index));

    // ASCII escape character
    else if (var[*index] == 'e')
        return case_e();

    // Hostname up to first part
    else if (var[*index] == 'h')
        return case_h();

    // Hostname
    else if (var[*index] == 'H')
        return case_H();

    // Newline
    else if (var[*index] == 'n')
    {
        if (var[*index + 1] == 'n' && var[*index + 2] == 'n')
            return case_nnn();

        else
            return case_n();
    }

    // Carriage return
    else if (var[*index] == 'r')
        return case_r();

    // Name of the shell, basename of $0
    else if (var[*index] == 's')
        return case_s();

    // Username
    else if (var[*index] == 'u')
        return case_u();

    // Current working directory, with $HOME abbreviated with a tilde
    else if (var[*index] == 'w')
        return case_w();

    // Basename of current working directory
    else if (var[*index] == 'W')
        return case_W();

    // If effective UID is 0, a #, otherwise a $
    else if (var[*index] == '$')
        return case_dollar_sign();

    // Backslash
    else if (var[*index] == '\\')
        return case_backslash();

    // Begin sequence of non-printing characters
    else if (var[*index] == '[')
        return case_open_bracket();

    return NULL;
}
