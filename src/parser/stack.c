#include "parser.h"

struct stack *stack_init(struct ast *root)
{
    struct stack *stack = calloc(1, sizeof(struct stack));
    stack_push(stack, symbol_create(0, RULE_INPUT), root);
    return stack;
}

static void stack_elt_ast_init(struct stack_elt *elt)
{
    if (!elt)
        return;
    if (elt->symbol->type == SYMBOL_TOKEN)
    {
        if (token_type_is_value(elt->symbol->token_type))
        {
            elt->ast = ast_init("", OPERATOR_NONE);
        }
    }
    else
    {
        enum operator_type operator = rule_id_to_operator(
                elt->symbol->rule_id);
        char *node_name = rule_id_to_string(elt->symbol->rule_id);
        elt->ast = ast_init(node_name, operator);
    }

}

void stack_push(struct stack *stack, struct symbol *s, struct ast *parent)
{
    struct stack_elt *elt = calloc(1, sizeof(struct stack_elt));
    elt->next = stack->head;
    elt->symbol = s;
    stack_elt_ast_init(elt);
    if (elt->ast)
    {
        ast_add_child(parent, elt->ast);
    }
    stack->head = elt;
    stack->size++;
}

void stack_push_array(struct stack *stack, struct symbol_array *symbols,
        struct ast *ast)
{
    int i = symbols->size - 1;
    for (; i >= 0; i--)
    {
        stack_push(stack, symbol_dup(symbols->array[i]), ast);
    }
    symbol_array_free(symbols);
}

struct stack_elt *stack_peak(struct stack *stack)
{
    if (stack->size == 0)
        return NULL;
    return stack->head;
}

struct stack_elt *stack_pop(struct stack *stack)
{
    if (stack->size == 0)
        return NULL;
    struct stack_elt *head = stack->head;
    stack->head = stack->head->next;
    stack->size--;
    return head;
}

void stack_elt_free(struct stack_elt *elt)
{
    if (!elt)
        return;
    free(elt->symbol);
    free(elt);
}

void stack_free(struct stack *stack)
{
    if (!stack)
        return;
    while (stack->size)
    {
        struct stack_elt *head = stack_pop(stack);
        stack_elt_free(head);
    }
    free(stack);
}

void stack_print(struct stack *stack)
{
    printf("-- STACK of size %zu\n", stack->size);
    struct stack_elt *it = stack->head;
    size_t count = stack->size - 1;
    while (it)
    {
        printf("[%zu] ", count);
        symbol_print(it->symbol);
        printf("\n");
        count--;
        it = it->next;
    }
    printf("----------\n");
}
