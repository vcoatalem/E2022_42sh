#include "parser.h"

struct symbol_array *substitute_rule(enum rule_id rule_id,
        enum token_type token_type, struct analysis_table *table)
{
    struct symbol_array *expr = table->transformation_mat[rule_id][token_type];
    if (!expr)
    {
        return NULL;
    }
    return symbol_array_dup(expr);
}

int parse(struct token_array *tokens, struct analysis_table *table)
{
    struct stamp *input = stamp_init(tokens);
    struct stack *stack = stack_init();
    while (!stamp_is_over(input))
    {
        struct token *current = stamp_read(input);
        struct symbol *pop = stack_pop(stack);
        if (pop->type == SYMBOL_TOKEN)
        {
            if (pop->token_type == current->type)
            {
                //failure
                return 1;
            }
        }
        else if (pop->type == SYMBOL_RULE)
        {
            struct symbol_array *arr = substitute_rule(
                    pop->rule_id, current->type, table);
            if (!arr)
            {
                //failure
                return 1;
            }
            else
            {
                stack_push_array(stack, arr);
            }
        }
        free(pop);
        stamp_continue(input);
    }
    int return_value = stack->size == 0;
    stack_free(stack);
    stamp_free(input);
    return return_value;
}
