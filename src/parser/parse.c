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
    #if 0
    printf("substitute_rule %d for token type %d: ", rule_id, token_type);
    symbol_array_print(expr);
    printf("\n");
    #endif
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

void parser_free(struct parser *parser)
{
    if (!parser)
        return;
    stamp_free(parser->input);
    stack_free(parser->stack);
    free(parser);
}

//if the only token left after an error is a token EOF
//set parser_state_continue instrad of parser_state_error
static void set_parsing_ending_status(struct parser *parser,
        enum token_type current_token_type)
{
    if (current_token_type == TOKEN_EOF)
        parser->state = PARSER_STATE_CONTINUE;
    else
        parser->state = PARSER_STATE_FAILURE;
}

//TODO: refactorize this once figured out. Also, leeks.
void parse(struct parser *parser, struct analysis_table *table)
{
    printf("[LL PARSER] entered parsing\n");
    struct stamp *input = parser->input;
    struct stack *stack = parser->stack;
    while (!stamp_is_over(input))
    {
        #if 0
        stack_print(stack);
        stamp_print(input);
        #endif
        //in case we just popped an epsilon rule, we dont want to get next
        //symbol on stamp
        struct token *current = stamp_read(input);
        #if 0
        printf("[LL PARSER] current head of stamp: %s\n",
                token_to_formatted_string(current->type));
        #endif
        struct stack_elt *head = stack_pop(stack);
        if (head->symbol->type == SYMBOL_TOKEN)
        {
            if (head->symbol->token_type != current->type)
            {
                set_parsing_ending_status(parser, current->type);
                return;
            }
            if (current->type == TOKEN_WORD)
            {
                //get current word value into the ast
                //TODO: give this treatment to more types (eg. excl point)
                head->ast->value = my_strdup(current->value);
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
                    set_parsing_ending_status(parser, current->type);
                    //could not find correspondance in analysis table
                    return;
                }
                else
                {
                    //current top of stack rule is an epsilon rule, therefore
                    //can be canceled. 
                    symbol_array_free(is_epsilon);
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
    #if 0
    stack_print(stack);
    #endif
    parser->state = stack->size == 0 ?
            PARSER_STATE_SUCCESS : PARSER_STATE_CONTINUE;
    printf("[LL PARSER] done parsing. state: %d\n", parser->state);
}
