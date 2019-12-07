#include "lexer.h"
#include "../hashtable/hashtablevar.h"
#include <string.h>
#include <ctype.h>

struct token_array *token_array_init()
{
    struct token_array *res = calloc(1, sizeof(struct token_array));
    if (!res)
        return NULL;
    res->capacity = 4;
    res->size = 0;
    res->tok_array = calloc(res->capacity, sizeof(void *));
    if (!res->tok_array)
        return NULL;
    return res;
}

void token_array_free(struct token_array *arr)
{
    if (!arr)
        return;
    for(size_t i = 0; i < arr->size; i++)
    {
        token_free(arr->tok_array[i]);
    }
    free(arr->tok_array);
    free(arr);
}

void token_array_add(struct token_array *arr, struct token *token)
{
    if (token->type == TOKEN_WORD && !token->quoted)
    {
        for (size_t i = 0; i < strlen(token->value); ++i)
        {
            //we check whether or not the token we wish to expand contains
            //one of the char specific to expansion
            if ((token->value[i] == '*' || token->value[i] == '?'
                || token->value[i] == '[')
                    && strcmp(token->value, "$?")) //TODO: handle this better
            {
                token->type = TOKEN_WORD_EXPAND;
            }
        }
    }

    arr->tok_array[arr->size] = token;
    arr->size++;
    if (arr->size == arr->capacity)
    {
        arr->capacity = arr->capacity * 2;
        arr->tok_array = realloc(arr->tok_array, arr->capacity
                * sizeof(void*));
    }
}

void token_array_remove(struct token_array *arr, size_t n)
{
    if (!arr || n >= arr->size)
    {
        return;
    }
    token_free(arr->tok_array[n]);
    for (; n < arr->size; n++)
    {
        arr->tok_array[n] = arr->tok_array[n + 1];
    }
    arr->size--;
}

/*Useful when we are in interactive mode and we want to merge two arrays
  We have to stick the last token of the first array with the first token of
  the second array with a \n between them*/
void token_arrays_fusion(struct token_array *arr1, struct token_array *arr2)
{
    if (arr1->size == 0)
    {
        for (size_t i = 0; i < arr2->size; ++i)
        {
            token_array_add(arr1, arr2->tok_array[i]);
        }
        return;
    }

    size_t lena = strlen(arr1->tok_array[arr1->size - 1]->value);
    size_t lenb = strlen(arr2->tok_array[0]->value);
    size_t len = lena + lenb + 1;
    arr1->tok_array[arr1->size - 1]->value =
        realloc(arr1->tok_array[arr1->size - 1]->value, len);
    memcpy(arr1->tok_array[arr1->size - 1]->value + lena,
            arr2->tok_array[0]->value, lenb + 1);
    arr1->tok_array[arr1->size - 1]->type = TOKEN_WORD;
    for (size_t i = 1; i < arr2->size; i++)
    {
        token_array_add(arr1, arr2->tok_array[i]);
    }
}

void token_array_print(struct token_array *arr, FILE *out)
{
    for (size_t i = 0; i < arr->size; i++)
    {
        fprintf(out, "-> [ %s : `%s` ]",
                token_to_formatted_string(arr->tok_array[i]->type),
                arr->tok_array[i]->value);
    }
    fprintf(out, "\n");
}

static int search_unique_equal(char *buffer)
{
    int occ = 0;
    int index = 0;
    for (int i = 0; buffer[i]; i++)
    {
        if (buffer[i] == '=')
        {
            occ++;
            index = i;
        }
    }
    if (occ != 1)
        return 0;
    return index;
}

static int is_assignment(char *buffer, int equal, int is_string)
{
    if (isdigit(buffer[0]))
        return 0;
    if (is_string)
        return 1;
    for (int i = 0; i < equal; i++)
    {
        if (is_separator(buffer[i])
                || (!isalnum(buffer[i]) && buffer[i] != '_'))
        {
            return 0;
        }
    }
    for (int j = equal + 1; buffer[j]; j++)
    {
        if (is_separator(buffer[j]))
            return 0;
    }
    return 1;
}

void check_assignment(char *buffer, struct token_array *arr, int is_string,
    struct hash_table_var *hash_table_aliases)
{
    int assignment = 0;
    int tmp = search_unique_equal(buffer);
    if (tmp)
    {
        assignment = is_assignment(buffer, tmp, is_string);
    }
    if (assignment)
        token_array_add(arr, token_init(TOKEN_ASSIGNMENT, buffer));
    else if (strcmp(buffer, "$()") == 0)
        token_array_add(arr, token_init(TOKEN_SUBSHELL, ""));
    else
    {

        if (is_string == 2)
            token_array_add(arr, token_init(TOKEN_WORD_NO_SUBSTITUTION, buffer));
        else
        {
            struct token *tok = NULL;
            if (buffer[0] == '~' && is_string == 0)
                tok = token_init(TOKEN_WORD_TILDE, buffer);
            else
                tok = token_init(TOKEN_WORD, buffer);
            if (is_string)
                tok->quoted = 1;
            if (hash_table_aliases && (arr->size == 0
                || !token_is_word(arr->tok_array[arr->size - 1])))
            {
                if (strcmp(get_variable(hash_table_aliases, buffer), ""))
                {
                    struct lexer *lexer2 = lexer_init(NULL);
                    lexer_add_string(lexer2, get_variable(hash_table_aliases,
                            buffer));
                    struct token_array *tok_array2 = lex(lexer2);
                    for (size_t i = 0; i < tok_array2->size - 1; ++i)
                    {

                        struct token *token = token_init(tok_array2->tok_array[i]->type,
                            (tok_array2->tok_array[i]->value));
                        token_array_add(arr, token);
                    }
                    token_array_free(tok_array2);
                    lexer_free(lexer2);
                    token_free(tok);
                }
                else
                    token_array_add(arr, tok);
            }
            else
                token_array_add(arr, tok);
        }
    }

}

void handle_separators(char *str, size_t *iterator, char *buffer,
        size_t *index, struct token_array *arr, int is_string,
        struct hash_table_var *hash_table_aliases)
{
    if (*index > 0)
    {
        check_assignment(buffer, arr, is_string, hash_table_aliases);
        *index = 0;
    }
    if (is_space(str[*iterator]))
    {
        *iterator = *iterator + 1;
        if (str[*iterator] == '#')
            while(str[*iterator] != '\n' && str[*iterator] != 0)
                *iterator = *iterator + 1;
        return;
    }
    while (str[*iterator] && !is_space(str[*iterator]))
    {
        buffer[*index] = str[*iterator];
        buffer[*index + 1] = 0;
        *index = *index + 1;
        *iterator = *iterator + 1;
        enum token_type type = token_check(str, *iterator, buffer);
        if (type != TOKEN_WORD)
        {
            //printf("single quote 3\n");
            token_array_add(arr, token_init(type, buffer));
            break;
        }
    }
    *index = 0;
}

struct token_array *token_array_create(char *str)
{
    size_t iterator = 0;
    char buffer[2048] = { 0 };
    struct token_array *arr = token_array_init();
    size_t index = 0;
    enum token_type type = TOKEN_EOF;
    while (str[iterator] != 0)
    {
        if (is_separator(str[iterator]))
        {
            handle_separators(str, &iterator, buffer, &index, arr, 0, NULL);
        }
        else
        {
            buffer[index] = str[iterator];
            buffer[index + 1] = 0;
            index++;
            iterator++;
            type = token_check(str, iterator, buffer);
            if (type != TOKEN_WORD && is_separator(str[iterator]))
            {
                struct token *token = token_init(type, buffer);
                token_array_add(arr, token);
                index = 0;
            }
        }
    }

    if (index > 0)
    {
        enum token_type tok = token_check(buffer, 0, buffer);
        if (tok == TOKEN_WORD)
            check_assignment(buffer, arr, 0, NULL);
        else
            token_array_add(arr, token_init(tok,buffer));
    }
    token_array_add(arr, token_init(TOKEN_EOF, ""));
    return arr;
}
