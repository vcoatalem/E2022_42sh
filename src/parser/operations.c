#include "parser.h"

//all tokens that may be at the start of expression
struct symbol_array *first(struct symbol_array *expression,
        struct rule_array *rules)
{
    struct symbol *first_symbol = *(expression->array);
    if (first_symbol->type == SYMBOL_EPSILON)
    {
        return NULL;
    }
    struct symbol_array *array = symbol_array_init();
    if (first_symbol->type == SYMBOL_TOKEN)
    {
        symbol_array_add(array, symbol_dup(first_symbol));
    }
    else if (first_symbol->type == SYMBOL_RULE)
    {
        //if first symbol refers to a rule, we search through all the rules
        //for that symbol and add their first()
        for (size_t i = 0; i < rules->size; i++)
        {
            struct rule *current = rules->rules[i];
            if (current->rule_id == first_symbol->rule_id)
            {
                struct symbol_array *sub = first(
                    rules->rules[i]->symbols, rules);
                if (sub)
                { 
                    symbol_array_merge(array, sub);
                    symbol_array_free(sub);
                }
            }
        }
    }
    #if 0
    /**/printf("first for ");
    /**/symbol_array_print(expression);
    /**/printf(": ");
    /**/symbol_array_print(array);
    /**/printf("\n");
    #endif
    return array;
}

//all tokens that may follow rule
struct symbol_array *next(enum rule_id rule_id, struct rule_array *rules)
{
    struct symbol_array *array = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        struct symbol_array *expr = (rules->rules[i])->symbols;
        for (size_t j = 0; j < expr->size; j++)
        {
            struct symbol *current = expr->array[j];
            if (current->type == SYMBOL_RULE && current->rule_id == rule_id)
            {
                //found an occurence of the symbol we research
                struct symbol *next_symbol = j != expr->size - 1 ?
                    expr->array[j + 1] : symbol_end();
                #if 0
                /**/printf("next symbol: ");
                /**/symbol_print(next_symbol);
                /**/printf("\n");
                #endif
                //same treatment as first here
                if (next_symbol->type == SYMBOL_TOKEN)
                {
                    symbol_array_add(array, symbol_dup(next_symbol));
                }
                else if (next_symbol->type == SYMBOL_RULE)
                {
                    //if first symbol refers to a rule, we search through all the rules
                    //for that symbol and add their first()
                    for (size_t i = 0; i < rules->size; i++)
                    {
                        struct rule *current = rules->rules[i];
                        if (current->rule_id == next_symbol->rule_id)
                        {
                            struct symbol_array *sub = first(
                                (rules->rules[i])->symbols, rules);
                            if (sub)
                            {
                                symbol_array_merge(array, sub);
                                symbol_array_free(sub);
                            }
                        }
                    }
                }
            }
        }
    }
    return array;
}

int epsilon(struct symbol_array *expression)
{
    return (*(expression->array))->type == SYMBOL_EPSILON;
}
