#include "parser.h"

static struct symbol_array *get_symbol_first(struct symbol_array *expression,
    size_t n, struct rule_array *rules)
{
    if (n == expression->size)
    {
        return NULL;
    }
    struct symbol *symbol = expression->array[n];
    if (symbol->type == SYMBOL_EPSILON)
    {
        return NULL;
    }
    struct symbol_array *array = symbol_array_init();
    if (symbol->type == SYMBOL_TOKEN)
    {
        if (!symbol_array_contains(array, symbol))
            symbol_array_add(array, symbol_dup(symbol));
    }
    else if (symbol->type == SYMBOL_RULE)
    {
        //if first symbol refers to a rule, we search through all the rules
        //for that symbol and add their first()
        if (rule_is_epsilon(symbol->rule_id, rules))
        {
            //if the rule found is skippable, we return to our expression_list
            //and do the same operation onto the next symbol
            struct symbol_array *pass = get_symbol_first(expression, n + 1,
                    rules);
            if (pass)
            {
                symbol_array_merge(array, pass);
                symbol_array_free(pass);
            }
        }
        //regardless, of the rule is skippable or not
        for (size_t i = 0; i < rules->size; i++)
        {
            struct rule *current = rules->rules[i];
            if (current->rule_id == symbol->rule_id)
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
    return array;
}

//all terminals(token) that may be at the start of expression
struct symbol_array *first(struct symbol_array *expression,
        struct rule_array *rules)
{
    struct symbol_array *array = get_symbol_first(expression, 0, rules);
    if (array)
    {
    #if 0
        /**/printf("first for ");
        /**/symbol_array_print(expression);
        /**/printf(": ");
        /**/symbol_array_print(array);
        /**/printf("\n");
    #endif
    }
    return array;
}

#if 0
static struct symbol_array *first_of_rule(enum rule_id, struct rule_array *rules)
{
    struct symbol_array *array = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        if (rule_id == array->rules[i]->rule_id)
        {
            struct symbol_array *sub = first(array->rules[i]->symbols,
                    rules);
            if (sub)
            {
                symbol_array_merge(array, sub);
                symbol_array_free(sub);
            }
        }
    }
    return array
}
#endif

//all terminals(tokens) that may follow rule
struct symbol_array *next(enum rule_id rule_id, struct rule_array *rules)
{
    //printf("--- ENTERED NEXT for RULE #%d\n", rule_id);
    struct symbol_array *array = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        struct symbol_array *expr = (rules->rules[i])->symbols;
        for (size_t j = 0; j < expr->size; j++)
        {
            struct symbol *current = expr->array[j];
            if (current->type == SYMBOL_RULE && current->rule_id == rule_id)
            {
                //we found the rule we are seaching for in an exp
                if (j < expr->size - 1)
                {
                    //if it is not at the end of the expression, get
                    //the next symbol in the same expression
                    struct symbol *next_symbol = expr->array[j + 1];
                    #if 0
                    /**/printf("RULE #%d; NEXT SYMBOL:", rule_id);
                    /**/symbol_print(next_symbol);
                    /**/printf("\n");
                    #endif
                    if (next_symbol->type == SYMBOL_TOKEN)
                    {
                        if (!symbol_array_contains(array, next_symbol))
                            symbol_array_add(array, symbol_dup(next_symbol));
                    }
                    else if (next_symbol->type == SYMBOL_RULE)
                    {
                        if (rule_is_epsilon(next_symbol->rule_id,
                                rules))
                        {
                            //if the rule represented by the next symbol is
                            //an epsilon-rule, add its next to the current next
                            struct symbol_array *pass = next(next_symbol->rule_id,
                                    rules);
                            if (pass)
                            {
                                symbol_array_merge(array, pass);
                                symbol_array_free(pass);
                            }
                        }
                        //if first symbol refers to a rule, we search through all the rules
                        //for that symbol and add their first()
                        for (size_t i = 0; i < rules->size; i++)
                        {
                            struct rule *current = rules->rules[i];
                            if (current->rule_id == next_symbol->rule_id)
                            {
                                struct symbol_array *expr = rules->rules[i]->symbols;
                                struct symbol_array *sub = first(expr, rules);
                                if (sub)
                                {
                                    symbol_array_merge(array, sub);
                                    symbol_array_free(sub);
                                }
                            }
                        }
                    }
                }
                else
                {
                    struct symbol *end = symbol_end();
                    //if the searched symbol is at the end of the expr,
                    //add symbol_end (?) and first of all the rules of the
                    //rule_id of the expr 
                    if (!symbol_array_contains(array, end))
                        symbol_array_add(array, end); //TODO: check leaks here
                    //except in the case the rule is the same as the current
                    //expression we are examinating
                    if (rules->rules[i]->rule_id != current->rule_id)
                    {
                        struct symbol_array *next_rule = next(
                                rules->rules[i]->rule_id, rules);
                        if (next_rule)
                        {
                            symbol_array_merge(array, next_rule);
                            symbol_array_free(next_rule);
                        }
                    }
                }
            }
        }
    }
    #if 0
    /**/printf("EXITING NEXT for RULE #%d with array: ", rule_id);
    /**/symbol_array_print(array);
    /**/printf("\n");
    #endif
    return array;
}

int expr_is_epsilon(struct symbol_array *expression)
{
    return (*(expression->array))->type == SYMBOL_EPSILON;
}

int rule_is_epsilon(enum rule_id rule_id, struct rule_array *rules)
{
    for (size_t i = 0; i < rules->size; i++)
    {
        struct rule *curr = rules->rules[i];
        if (curr->rule_id == rule_id)
        {
            int is_epsilon = expr_is_epsilon(curr->symbols);
            if (is_epsilon)
                return 1;
        }
    }
    return 0;
}
