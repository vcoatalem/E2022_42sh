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
        arr->tok_array = realloc(arr->tok_array, arr->capacity
                * sizeof(void*));
    }
}
/*Useful when we are in interactive mode and we want to fusionate two arrays
We have to stick the last token of the first array with the first token of 
the second array with a \n between them*/
void token_arrays_fusion(struct token_array *arr1, struct token_array *arr2)
{

    size_t lena = strlen(arr1->tok_array[arr1->size - 1]->value);
    size_t lenb = strlen(arr2->tok_array[0]->value);
    size_t len = lena + lenb + 1;
    arr1->tok_array[arr1->size - 1]->value =
    realloc(arr1->tok_array[arr1->size - 1]->value, len);
    memcpy(arr1->tok_array[arr1->size - 1]->value + lena,
    arr2->tok_array[0]->value, lenb + 1);
    arr1->tok_array[arr1->size - 1]->type = TOKEN_WORD;
    
    for(size_t i = 1; i < arr2->size; i++)
    {
        //TODO add free for token
        token_array_add(arr1, arr2->tok_array[i]);
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

int is_separator(char c)
{
    return (c == ' ' || c == '\t' || c == '|' || c == '&' || c == '\n'
         || c == '(' || c == ')' || c == '\0' || c == '<' || c == '>'
         || c == ';');
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

void handle_separators(char *str, size_t *iterator, char *buffer,
        size_t *index, struct token_array *arr)
{ 
    if (*index > 0)
    {
        token_array_add(arr, token_init(TOKEN_WORD, buffer));
        *index = 0;
    }
    if (is_space(str[*iterator]))
    {
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
            handle_separators(str, &iterator, buffer, &index, arr);
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
        token_array_add(arr, token_init(token_check(buffer, 0, buffer), buffer));
    token_array_add(arr, token_init(TOKEN_EOF, ""));;
    return arr;
}
