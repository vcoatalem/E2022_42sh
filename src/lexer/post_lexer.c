#include "lexer.h"

//returns token at position #n in array, or NULL if it does not exist
static struct token *get_token(struct token_array *array, size_t n)
{
    if (n >= array->size)
    {
        return NULL;
    }
    return array->tok_array[n];
}

//merge adjacent Word, ( and ) into a function declaration
static void create_funcdec_tokens(struct token_array *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
        struct token *t = get_token(array, i);
        if (t && t->type == TOKEN_WORD)
        {
            struct token *left_parenthesis = get_token(array, i + 1);
            struct token *right_parenthesis = get_token(array, i + 2);
            if (!left_parenthesis || !right_parenthesis)
                continue;
            if (left_parenthesis->type == TOKEN_LEFT_PARENTHESIS
                    && right_parenthesis->type == TOKEN_RIGHT_PARENTHESIS)
            {
                token_array_remove(array, i + 1);
                // i + 2 is now at pos i + 1
                token_array_remove(array, i + 1);
                t->type = TOKEN_FUNCDEC;
            }
        }
    }
}

void post_lexing_treatment(struct token_array *tokens)
{
    if (!tokens)
        return;
    create_funcdec_tokens(tokens);
}
