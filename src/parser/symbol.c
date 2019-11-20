#include "parser.h"

struct symbol *symbol_epsilon(void)
{
    struct symbol *res = calloc(1, sizeof(struct symbol));
    res->type = SYMBOL_EPSILON;
    return res;
}

struct symbol *symbol_end(void)
{
    struct symbol *res = calloc(1, sizeof(struct symbol));
    res->type = SYMBOL_END;
    return res;
}

struct symbol *symbol_create(enum token_type token_type, enum rule_id rule_id)
{
    struct symbol *res = calloc(1, sizeof(struct symbol));
    if (rule_id == RULE_NONE)
    {
        //terminal symbol
        res->type = SYMBOL_TOKEN;
        res->token_type = token_type;
    }
    else
    {
        res->type = SYMBOL_RULE;
        res->rule_id = rule_id;
    }
    return res;
}

struct symbol *symbol_dup(struct symbol *s)
{
    if (s->type == SYMBOL_EPSILON)
        return symbol_epsilon();
    else if (s->type == SYMBOL_END)
        return symbol_end();
    return symbol_create(s->token_type, s->rule_id);
}

void symbol_print(struct symbol *s)
{
    if (s->type == SYMBOL_EPSILON)
    {
        printf("epsilon");
    }
    else if (s->type == SYMBOL_END)
    {
        printf("$");
    }
    else if (s->type == SYMBOL_RULE)
    {
        printf("{R #%d}", s->rule_id);
    }
    else
    {
        printf("{T `%s`}", token_to_formatted_string(s->token_type));
    }
}
