#include "parser.h"

static char *my_strdup(char *str)
{
    size_t size = 0;
    while (*(str + size))
    {
        size++;
    }
    char *s = calloc(1, size + 1);
    strcpy(s, str);
    return s;
}

struct symbol_array *substitute_rule(enum rule_id rule_id,
        int token_type, struct analysis_table *table)
{
    struct symbol_array *expr = table->transformation_mat[rule_id][token_type];
    printf("substitute_rule %d for token type %d: ", rule_id, token_type);
    symbol_array_print(expr);
    printf("\n");
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

//TODO: refactorize this once figured out. Also, leeks.
void parse(struct parser *parser, struct analysis_table *table)
{
    printf("[LL PARSER] entered parsing\n");
    struct stamp *input = parser->input;
    struct stack *stack = parser->stack;
    struct token *current = NULL;
    int should_read_input = 1;
    while (!stamp_is_over(input))
    {
        stack_print(stack);
        stamp_print(input);
        //in case we just popped an epsilon rule, we dont want to get next
        //symbol on stamp
        if (should_read_input)
        {
            current = stamp_read(input);
        }
        else
        {
            should_read_input = 1;
        }
        printf("[LL PARSER] current head of stamp: %s\n",
                token_to_formatted_string(current->type));
        struct stack_elt *head = stack_pop(stack);
        if (head->symbol->type == SYMBOL_TOKEN)
        {
            if (head->symbol->token_type != current->type)
            {
                parser->state = PARSER_STATE_FAILURE;
                return;
            }
            if (current->type == TOKEN_WORD)
            {
                head->ast->content.value = my_strdup(current->value);
            }
            stamp_continue(input);
        }
        else if (head->symbol->type == SYMBOL_RULE)
        {
            struct symbol_array *arr = substitute_rule(
                    head->symbol->rule_id, current->type, table);
            if (!arr)
            {
                struct symbol_array *is_epsilon = substitute_rule(
                    head->symbol->rule_id, table->n_symbols - 1, table);
                if (!is_epsilon)
                {
                    parser->state = PARSER_STATE_FAILURE;
                    //could not find correspondance in analysis table
                    return;
                }
                else
                {
                    //current top of stack rule is an epsilon rule, therefore
                    //can be canceled. 
                    symbol_array_free(is_epsilon);
                    should_read_input = 0;
                    continue;
                
                }
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
    //TODO: try to factorise this with main loop
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
    stack_print(stack);
    if (stack->size == 0)
        parser->state = PARSER_STATE_SUCCESS;
}
