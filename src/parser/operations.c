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

struct symbol_array *expr_first(struct rule *rule, struct rule_array *rules)
{
    struct symbol_array *res = symbol_array_init();
    struct symbol_array *expression = rule->symbols;
    #if 0
    printf("entered expr_first for expr: ");
    symbol_array_print(expression);
    printf("\n");
    #endif
    size_t index = 0;
    
    while (index < expression->size)
    {
        struct symbol *s = expression->array[index];
        if (s->type == SYMBOL_TOKEN)
        {
            //if first symbol in expr is a token, add it to the list
            symbol_array_add_if_not_in(res, symbol_dup(s));
        }
        else if (s->type == SYMBOL_RULE && rule->rule_id != s->rule_id)
        {
            //if first symbol in expr is a rule, add rule_first() of this rule
            symbol_array_merge(res, rule_first(s->rule_id, rules));
            if (rule_is_epsilon(s->rule_id, rules))
            {
                index++;
                continue;
            }
        }
        break;
    }
    return res;
    printf("[LL PARSER] expr first for ");
    symbol_array_print(expression);
    printf(" returning: ");
    symbol_array_print(res);
    printf("\n");
}

struct symbol_array *rule_first(enum rule_id rule_id, struct rule_array *rules)
{
    #if 0
    printf("entered rule_first %d\n", rule_id);
    #endif
    struct symbol_array *res = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        struct rule *current = rules->rules[i];
        //for each rule in rules...
        if (current->rule_id == rule_id)
        {
            #if 0
            printf("rule_first %d ; found occcurence in rule #%zu: ", rule_id, i);
            symbol_array_print(current->symbols);
            printf("\n");
            #endif
            symbol_array_merge(res, expr_first(current, rules));
        }
    }
    printf("[LL PARSER] rule first for id %d returning: ", rule_id);
    symbol_array_print(res);
    printf("\n");
    return res;
}

struct symbol_array *rule_next(enum rule_id rule_id, struct rule_array *rules)
{
    #if 0
    printf("[TABLE] entered rule_next(%d)\n", rule_id);
    #endif
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
                    symbol_array_add_if_not_in(res, NULL); 
                }
                else if (next_symbol->type == SYMBOL_TOKEN)
                {
                    //if next symbol is a token, add it
                    symbol_array_add_if_not_in(res, symbol_dup(next_symbol));
                }
                else if (next_symbol->type == SYMBOL_RULE)
                {
                    //if next symbol is a rule, add rule_first()
                    symbol_array_merge(res, rule_first(rule->rule_id, rules));
                }
            }
        }
    }
    printf("[LL PARSER] rule next for id %d returning: ", rule_id);
    symbol_array_print(res);
    printf("\n");
    return res;
}
