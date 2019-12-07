#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <libgen.h>

#include "42sh.h"

#define PATH_MAX 1024

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

    char *result = calloc(PATH_MAX, sizeof(char));
    size_t nb = strftime(result, PATH_MAX, "%A %B %d", tm);
    result = realloc(result, nb * sizeof(char) + 1);
    result[nb] = '\0';

    return result;
}

static char *get_format(char *var, size_t *index)
{
    char *format = NULL;
    size_t nb = 0;

    for (; var[*index] != '\0'; (*index)++)
    {
        if (var[*index] == '}')
            break;

        format = realloc(format, (nb + 1) + sizeof(char));
        format[nb] = var[*index];
        format[nb + 1] = '\0';
        nb++;
    }

    return format;
}

static char *case_D(char *format)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char *result = calloc(PATH_MAX, sizeof(char));
    size_t nb = strftime(result, PATH_MAX, format, tm);
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

static char *case_h()
{
    char *hostname = calloc(PATH_MAX, sizeof(char));
    gethostname(hostname, 1023);
    hostname = strtok(hostname, ".");

    return hostname;
}

static char *case_H()
{
    char *hostname = calloc(PATH_MAX, sizeof(char));
    gethostname(hostname, 1023);

    return hostname;
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

static char *case_s()
{
    char *result = calloc(PATH_MAX, sizeof(char));
    result = strcat(result, basename(getenv("SHELL")));

    return result;
}

static char *case_u()
{
    char *result = calloc(PATH_MAX, sizeof(char));
    getlogin_r(result, 1023);

    return result;
}

static char *case_w()
{
    char *result = calloc(PATH_MAX, sizeof(char));
    result = getcwd(result, 1023);

    if (strcmp(result, getenv("HOME")) == 0)
    {
        result = realloc(result, 2 * sizeof(char));
        result[0] = '~';
        result[1] = '\0';
    }

    return result;
}

static char *case_W()
{
    char *result = calloc(PATH_MAX, sizeof(char));
    result = getcwd(result, 1023);

    if (strcmp(result, getenv("HOME")) == 0)
    {
        result = realloc(result, 2 * sizeof(char));
        result[0] = '~';
        result[1] = '\0';
    }

    result = basename(result);

    return result;
}

static char *case_dollar_sign()
{
    char *result = calloc(PATH_MAX, sizeof(char));
    sprintf(result, "%d", getuid());

    return result;
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

char *case_var(char *var, size_t *index)
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
    {
        if (var[(*index) + 1] == '{')
        {
            (*index) += 2;
            return case_D(get_format(var, index));
        }

        return NULL;
    }

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

    return NULL;
}

char *replace_prompt(char *prompt)
{
    char new_prompt[4096] = { 0 };
    size_t i = 0;

    while (prompt[i] != '\0')
    {
        if (prompt[i] == '\\')
        {
            i++;
            char *var = case_var(prompt, &i);
            if (var != NULL)
            {
                strcat(new_prompt, var);
                free(var);
            }

            else
            {
                --i;
                new_prompt[i] = prompt[i];
            }
        }
        else
        {
            new_prompt[i] = prompt[i];
        }

        i++;
    }

    return strdup(new_prompt);
}
