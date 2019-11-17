#include "parser.h"

#if 0
struct stamp
{
    struct token_array *tokens;
    size_t pos;
};
#endif

struct stamp *stamp_init(struct token_array *tokens)
{
    struct stamp *s = calloc(1, sizeof(struct stamp));
    s->tokens = tokens;
    s->pos = 0;
    return s;
}

struct token *stamp_read(struct stamp *stamp)
{
    return *(stamp->tokens->tok_array + stamp->pos);
}

void stamp_continue(struct stamp *stamp)
{
    stamp->pos++;
}

void stamp_free(struct stamp *stamp)
{
    free(stamp);
}

int stamp_is_over(struct stamp *stamp)
{
    return stamp->pos == stamp->tokens->size;
}

void stamp_print(struct stamp *stamp)
{
    if (stamp_is_over(stamp))
    {
        printf("--- STAMP: over\n");
    }
    else
    {
        printf("--- STAMP: token %zu / %zu: %s\n", stamp->pos,
                stamp->tokens->size - 1,
                token_to_string(stamp_read(stamp)->type));
    }
}
