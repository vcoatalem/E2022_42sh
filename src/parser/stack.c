#include "parser.h"

struct stack *stack_init()
{
    struct stack *stack = calloc(1, sizeof(struct stack));
    stack_push(stack, symbol_create(0, RULE_COMMAND)); //put higher level command here
    return stack;
}

void stack_push(struct stack *stack, struct symbol *s)
{
    struct stack_elt *elt = calloc(1, sizeof(struct stack_elt));
    elt->next = stack->head;
    elt->symbol = s;
    stack->head = elt;
    stack->size++;
}

void stack_push_array(struct stack *stack, struct symbol_array *symbols)
{
    int i = symbols->size - 1;
    for (; i > 0; i--)
    {
        stack_push(stack, symbols->array[i]);
    }
}

struct symbol *stack_peak(struct stack *stack)
{
    if (stack->size == 0)
        return NULL;
    struct symbol *s = stack->head->symbol;
    return s;
}

struct symbol *stack_pop(struct stack *stack)
{
    if (stack->size == 0)
        return NULL;
    struct stack_elt *head = stack->head;
    struct symbol *s = head->symbol;
    stack->head = head->next; 
    free(head);
    stack->size--;
    return s;
}

void stack_free(struct stack *stack)
{
    while (stack->size)
        free(stack_pop(stack));
    free(stack);
}
