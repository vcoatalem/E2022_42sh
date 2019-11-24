#include "parser.h"

struct symbol_array *symbol_array_init(void)
{
    int initial_capacity = 4;
    struct symbol_array *res = calloc(1, sizeof(struct symbol_array));
    res->array = calloc(initial_capacity, sizeof(void*));
    res->capacity = initial_capacity;
    res->size = 0;
    return res;
}

void symbol_array_add(struct symbol_array *symbols, struct symbol *s)
{
    symbols->size = symbols->size + 1;
    if (symbols->size == symbols->capacity)
    {
        symbols->capacity *= 2;
        symbols->array = realloc(symbols->array,
            sizeof(void*) * symbols->capacity);
    }
    symbols->array[symbols->size - 1] = s;
}

int symbol_array_equal(struct symbol_array *s1, struct symbol_array *s2)
{
    if (s1->size != s2->size)
    {
        return 0;
    }
    for (size_t i = 0; i < s1->size; i++)
    {
        if (s1->array[i]->type != s2->array[i]->type)
        {
            return 0;
        }
        if (s1->array[i]->type == SYMBOL_TOKEN
                && s1->array[i]->token_type != s2->array[i]->token_type)
        {
            return 0;
        }
        else if (s1->array[i]->type == SYMBOL_RULE
                && s1->array[i]->rule_id != s2->array[i]->rule_id)
        {
            return 0;
        }
    }
    return 1;
}

void symbol_array_add_if_not_in(struct symbol_array *symbols,
        struct symbol *s)
{
    if (symbol_array_contains(symbols, s))
    {
        if (s)
        {
            free(s);
        }
        return;
    }
    if (s)
    {
        symbol_array_add(symbols, s);
    }
    else
        symbol_array_add(symbols, symbol_end());
}


struct symbol_array *symbol_array_dup(struct symbol_array *symbols)
{
    struct symbol_array *arr = calloc(1, sizeof(struct symbol_array));
    arr->capacity = symbols->capacity;
    arr->size = symbols->size;
    arr->array = calloc(sizeof(void*), arr->capacity);
    for (size_t i = 0; i < symbols->size; i++)
    {
        arr->array[i] = symbol_dup(symbols->array[i]);
    }
    return arr;
}

//used to prevent same tokens to appear multiple times in first() and next()
int symbol_array_contains(struct symbol_array *symbols, struct symbol *s)
{
    for (size_t i = 0; i < symbols->size; i++)
    {
        if (!s)
        {
            if (symbols->array[i]->type == SYMBOL_END)
            {
                return 1;
            }
        }
        else if (symbols->array[i]->type == s->type
            && symbols->array[i]->token_type == s->token_type)
        {
            return 1;
        }
    }
    return 0;
}

//used in first() and next() to build sub rule firsts and nexts
void symbol_array_merge(struct symbol_array *s1, struct symbol_array *s2)
{
    if (!s1 || !s2)
        return;
    for (size_t i = 0; i < s2->size; i++)
    {
        if (s2->array[i]->type == SYMBOL_TOKEN)
            symbol_array_add_if_not_in(s1, symbol_dup(s2->array[i]));
    }
    //if s2 contains a `$` but s1 does not
    if (!symbol_array_contains(s1, NULL) && symbol_array_contains(s2, NULL))
        symbol_array_add(s1, symbol_end());
    symbol_array_free(s2);
}

void symbol_array_free(struct symbol_array *s)
{
    for (size_t i = 0; i < s->size; i++)
    {
        free(s->array[i]);
    }
    free(s->array);
    free(s);
}

void symbol_array_print(struct symbol_array *s)
{
    if (!s)
    {
        printf("NULL");
        return;
    }
    printf("[");
    for (size_t i = 0; i < s->size; i++)
    {
        printf(" ");
        symbol_print(s->array[i]);
    }
    printf(" ]");
}
