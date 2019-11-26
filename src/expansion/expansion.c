#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>

#include "expansion.h"

static void left_shift(char *pattern, size_t index)
{
    for (; pattern[index] != '\0'; index++)
        pattern[index] = pattern[index + 1];
}

void clean_pattern(char *pattern)
{
    for (size_t i = 0; pattern[i] != '\0'; i++)
    {
        while (pattern[i] == '/' && pattern[i + 1] == '/')
            left_shift(pattern, i);
    }
}

int check_star(char *path, size_t *index, size_t size, char next)
{
    if (*index > size)
        return EXPANSION_FAILURE;

    for (; *index < size; (*index)++)
    {
        if (path[*index] == next)
            break;
    }

    return EXPANSION_SUCCESS;
}

int check_question_mark(size_t *index, size_t size)
{
    if (*index > size)
        return EXPANSION_FAILURE;

    (*index)++;

    return EXPANSION_SUCCESS;
}

static int is_logical_not(char *brackets)
{
    for (size_t i = 0; brackets[i] != '\0'; i++)
    {
        if (brackets[i] == '!')
            return 0;
    }

    return 1;
}

static int is_interval(char *brackets)
{
    for (size_t i = 0; brackets[i] != '\0'; i++)
    {
        if (brackets[i] == '-')
            return 0;
    }

    return 1;
}

static int _check_brackets_interval(char *path, size_t *index,
        char begin, char end)
{
    if (path[*index] >= begin && path[*index] <= end)
    {
        (*index)++;
        return EXPANSION_SUCCESS;
    }

    return EXPANSION_FAILURE;
}

static int _check_brackets(char *path, size_t *index,
        size_t char_size, char *characters)
{
    for (size_t i = 0; i < char_size; i++)
    {
        if (path[*index] == characters[i])
        {
            (*index)++;
            return EXPANSION_SUCCESS;
        }
    }

    return EXPANSION_FAILURE;
}

static int is_not_result(int result)
{
    return result == EXPANSION_SUCCESS ? EXPANSION_FAILURE : EXPANSION_SUCCESS;
}

int check_brackets(char *path, size_t *index, size_t size, char *brackets)
{
    int result = EXPANSION_FAILURE;
    if (*index > size)
        return EXPANSION_FAILURE;

    int is_not = 0;
    if (is_logical_not(brackets) == 0)
        is_not = 1;

    else if (is_interval(brackets) == 0)
    {
        for (size_t i = 1; brackets[i] != '\0'; i++)
        {
            if (brackets[i] == '-')
            {
                if (isalnum(brackets[i - 1]) == 0
                        || isalnum(brackets[i + 1]) == 0)
                    return EXPANSION_ERROR;

                result = _check_brackets_interval(path, index,
                        brackets[i - 1], brackets[i + 1]);
            }

            if (result == EXPANSION_SUCCESS)
                break;
        }
    }

    char *characters = malloc(sizeof(char *));
    size_t char_index = 0;
    for (size_t i = 1; brackets[i] != ']'; i++)
    {
        if (brackets[i] == ',')
            continue;
        if (brackets[i + 1] == '-')
        {
            i += 2;
            continue;
        }
        characters[char_index++] = brackets[i];
    }

    printf("%s\n", characters);
    if (result == EXPANSION_FAILURE)
        result = _check_brackets(path, index, char_index, characters);

    return is_not == 0 ? result : is_not_result(result);
}

// ### TEST
int main(void)
{
    //char *pattern = "*/[d]*";
    char *path = "dir2/dir22";

    size_t i = 0;
    printf("%d\n", check_brackets(path, &i, 10, "[0-9abcd]"));
    printf("i = %ld\n", i);

    return 0;
}
