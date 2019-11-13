#include "lexer.h"

struct token_array *token_array_init()
{
    struct token_array *res = malloc(sizeof(*res));
    if (!res)
        return NULL;
    res->capacity = 4;
    res->size = 0;
    res->tok_array = calloc(res->capacity, sizeof(struct token));
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
        //TODO add free for token
        free(arr->tok_array[i]);
    }
    free(arr->tok_array);
    free(arr);
}

void token_array_add(struct token_array *arr, struct token *token)
{
    arr->tok_array[arr->size] = token;
    arr->size++;
    if (arr->size == arr->capacity)
    {
        arr->capacity = arr->capacity * 2;
        arr->tok_array = realloc(arr->tok_array, arr->capacity);
    }
}

void token_array_print(struct token_array *arr, FILE *out)
{
    fprintf(out, "size of array: %ld\n", arr->size);
    for (size_t i = 0; i < arr->size; i++)
    {
        fprintf(out, "type: %s, value: `%s`\n",
            token_to_string(arr->tok_array[i]->type),
            arr->tok_array[i]->value);
    }
}

struct token_array *token_array_create(char *str)
{
    size_t iterator = 0;
    char buffer[2048];
    struct token_array *arr = token_array_init(); 
    size_t index = 0;
    while (str[iterator] != 0)
    {
        //TODO case where tokens are like this "toto>lol or toto(foo)"
        buffer[index] = str[iterator];
        index++;
        iterator++;
        buffer[index] = '\0';
        enum token_type type =  token_check(str, iterator, buffer);
        if (str[iterator] == ' ' || str[iterator] == '\n'
            || str[iterator] == '\0' || str[iterator] == '\t')
        {
            struct token *token = token_init(type, buffer);
            token_array_add(arr, token);
            index = 0;
        }
    }
    return arr;
}
