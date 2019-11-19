#include "parser.h"

int expr_is_epsilon(struct symbol_array *expression)
{
    return expression->array[0]->type == SYMBOL_EPSILON;
}

static int rule_is_epsilon(enum rule_id rule_id, struct rule_array *rules)
{
    for (size_t i = 0; i < rules->size; i++)
    {
        struct rule *curr = rules->rules[i];
        if (curr->rule_id == rule_id)
        {
            if (expr_is_epsilon(curr->symbols))
                return 1;
        }
    }
    return 0;
}

static struct symbol *get_next_symbol(struct symbol_array *expression,
        size_t i)
{
    if (expression->size == i - 1)
    {
        return NULL;
    }
    else
    {
        return expression->array[i + 1];
    }
}

#if 0
//returns the first() for any symbol in any expression  
static struct symbol_array *symbol_first(struct symbol_array *expression,
        size_t i, struct rule_array *rules)
{
    struct symbol *s = expression->array[i];
    struct symbol_array *res = symbol_array_init();
    if (s->type == SYMBOL_TOKEN)
    {
        //if first symbol in expr is a token, add it to the list
        if (!symbol_array_contains(res, s))
            symbol_array_add(res, s);
    }
    else if (s->type == SYMBOL_RULE)
    {
        //if first symbol in expr is a rule, add rule_first() of this rule
        symbol_array_merge(res, rule_first(s->rule_id, rules));
        if (rule_is_epsilon(s->rule_id, rules))
        {
            symbol_array_merge(res, rule_next(s->rule_id, rules));
        }
    }
    //handling of epsilon expr goes in rule_first
    return res;
}
#endif

struct symbol_array *expr_first(struct symbol_array *expression,
        struct rule_array *rules)
{
    struct symbol *s = expression->array[0];
    struct symbol_array *res = symbol_array_init();
    if (s->type == SYMBOL_TOKEN)
    {
        //if first symbol in expr is a token, add it to the list
        if (!symbol_array_contains(res, s))
            symbol_array_add(res, s);
    }
    else if (s->type == SYMBOL_RULE)
    {
        //if first symbol in expr is a rule, add rule_first() of this rule
        symbol_array_merge(res, rule_first(s->rule_id, rules));
        if (rule_is_epsilon(s->rule_id, rules))
        {
            symbol_array_merge(res, rule_next(s->rule_id, rules));
        }
    }
    //handling of epsilon expr goes in rule_first
    return res;
}

struct symbol_array *rule_first(enum rule_id rule_id, struct rule_array *rules)
{
    struct symbol_array *res = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        //for each rule in rules...
        if (rules->rules[i]->rule_id == rule_id)
        {
            //get expression of rule of the same id as the rule we called
            //rule_first() with
            struct symbol_array *expression = rules->rules[i]->symbols;
            if (expr_is_epsilon(expression))
            {
                //if the expression is epsilon, add rule_next() //TODO: should we ?
                symbol_array_merge(res, rule_next(rule_id, rules));
            }
            else
            {
                //else add expr_first()
                symbol_array_merge(res, expr_first(expression, rules));
            }
        }
    }
    return res;
}

struct symbol_array *rule_next(enum rule_id rule_id, struct rule_array *rules)
{
    printf("[TABLE] entered rule_next(%d)\n", rule_id);
    struct symbol_array *res = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        //for each rule in rules..
        struct rule *rule = rules->rules[i];
        struct symbol_array *expression = rule->symbols;
        for (size_t j = 0; j < expression->size; j++)
        {
            //for each symbol in rule..
            struct symbol *symbol = expression->array[j];
            if (symbol->type == SYMBOL_RULE && symbol->rule_id == rule_id)
            {
                // when we find a symbol that represents the rule
                // we called rule_next with ...
                struct symbol *next_symbol = get_next_symbol(expression, j);
                if (!next_symbol)
                {
                    //if there is no next symbol, add symbol_end
                    symbol_array_add(res, symbol_end()); 
                }
                else if (next_symbol->type == SYMBOL_TOKEN)
                {
                    //if next symbol is a token, add it
                    symbol_array_add(res, next_symbol);
                }
                else if (next_symbol->type == SYMBOL_RULE)
                {
                    //if next symbol is a rule, add rule_first()
                    symbol_array_merge(res, rule_first(rule->rule_id, rules));
                }
            }
        }
    }
    return res;
}
