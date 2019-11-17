#include "parser.h"

struct symbol_array *substitute_rule(enum rule_id rule_id,
        int token_type, struct analysis_table *table)
{
    struct symbol_array *expr = table->transformation_mat[rule_id][token_type];
    if (!expr)
    {
        return NULL;
    }
    return symbol_array_dup(expr);
}

struct parser *parser_init(struct token_array *tokens)
{
    struct parser *parser = calloc(1, sizeof(struct parser));
    parser->input = stamp_init(tokens);
    parser->ast = ast_init(NODE_OPERATOR, "root", OPERATOR_AND);
    parser->stack = stack_init(parser->ast);
    return parser;
}

void parser_free(struct parser *parser, int free_ast)
{
    stamp_free(parser->input);
    stack_free(parser->stack);
    if (free_ast)
        free(parser->ast);
    free(parser);
}

void parse(struct parser *parser, struct analysis_table *table)
{
    struct stamp *input = parser->input;
    struct stack *stack = parser->stack;
    while (!stamp_is_over(input))
    {
        stack_print(stack);
        stamp_print(input);
        struct token *current = stamp_read(input);
        struct stack_elt *head = stack_pop(stack);
        if (head->symbol->type == SYMBOL_TOKEN)
        {
            if (head->symbol->token_type != current->type)
            {
                return;
            }
            stamp_continue(input);
        }
        else if (head->symbol->type == SYMBOL_RULE)
        {
            struct symbol_array *arr = substitute_rule(
                    head->symbol->rule_id, current->type, table);
            if (!arr)
            {
                printf("could not find correspondance for popped rule in \
                    analysis table\n");
                return;
            }
            else
            {
                stack_push_array(stack, arr, head->ast);
            }
        }
        free(head);
    }
    //if stamp is over, try to find epsilon substitution for all symbols left
    //in stack
    printf("stamp over; stack left:\n");
    //TODO: try to factorise this with main loop
    stack_print(stack);
    while (stack->size != 0)
    {
        struct stack_elt *head = stack_pop(stack);
        struct symbol_array *arr = substitute_rule(
            head->symbol->rule_id, table->n_symbols - 1, table);
        free(head);
        if (!arr)
        {
            break;
        }
        else
        {
            symbol_array_free(arr);
        }
    }
    if (stack->size == 0)
        parser->state = PARSER_STATE_SUCCESS;
}
