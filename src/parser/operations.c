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
    if (expression->size == i + 1)
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
}

struct symbol_array *rule_first(enum rule_id rule_id, struct rule_array *rules)
{
    struct symbol_array *res = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        struct rule *current = rules->rules[i];
        //for each rule in rules...
        if (current->rule_id == rule_id)
        {
            symbol_array_merge(res, expr_first(current, rules));
        }
    }
    return res;
}

// search symbols representing the rule `rule_id` in expression of the
// rule `rule`. res, rules and path_list from rule_next()
// TODO: reduce the amount of arguments on this one
static void rule_next_find_handle_occurence(enum rule_id rule_id,
        struct rule *rule, struct symbol_array *res,
        struct rule_array *rules, int **path_list)
{
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
                if (!(*path_list)[rule->rule_id])
                {
                    //if there is no next symbol, add rule_next of the rule
                    //we are currently running through.
                    struct symbol_array *next = rule_next(rule->rule_id, rules,
                            path_list);
                    if (!next)
                    {
                        //meaning we already processed or are processing
                        //next(rule->rule_id, ...)
                    }
                    else if (next->size == 0)
                    {
                        //if rule does not have any next, add $ to the list
                        symbol_array_free(next);
                        symbol_array_add_if_not_in(res, NULL);
                    }
                    else
                    {
                        symbol_array_merge(res, next);
                    }
                }
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

struct symbol_array *rule_next(enum rule_id rule_id, struct rule_array *rules,
    int **path_list)
{
    int new_path_list[NB_RULES] = { 0 };
    int *new_path_list_ptr = new_path_list;
    if (!path_list)
    {
        path_list = &new_path_list_ptr;
    }
    if ((*path_list)[rule_id] == 1)
    {
        //if next() for this rule was already computed, return NULL
        return NULL;
    }
    (*path_list)[rule_id] = 1;
    struct symbol_array *res = symbol_array_init();
    for (size_t i = 0; i < rules->size; i++)
    {
        //for each rule in rules
        rule_next_find_handle_occurence(rules->rules[i]->rule_id,
                rules->rules[i], res, rules, path_list);
    }
    printf("\n");
    return res;
}
