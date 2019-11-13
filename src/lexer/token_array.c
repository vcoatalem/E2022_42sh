#include "lexer.h"

struct token_array *token_array_init()
{
    struct token_array *res = malloc(*res);
    if (!res)
        return NULL;
    res->capacity = 4;
    res->size = 0;
    res->tok_array = calloc(res->capacity, sizeof(struct token));
    if (!res->tok_array)
        return NULL;
    return res;
}

void token_array_free(struct token array *arr)
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
    arr->token_array[size] = token;
    size++;
    if (arr->size == arr->capacity)
    {
        arr->capacity = arr->capacity * 2;
        arr->tok_array = realloc(arr->tok_array, arr->capacity);
    }
}
