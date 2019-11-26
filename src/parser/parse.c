#include <err.h>

#include "parser.h"
#include "../main/42sh.h"

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
    if (!expr)
    {
        return NULL;
    }
    return symbol_array_dup(expr);
}

struct parser *parser_init(struct token_array *tokens,
        struct analysis_table *table)
{
    struct parser *parser = calloc(1, sizeof(struct parser));
    parser->table = table;
    parser->input = stamp_init(tokens);
    parser->ast = ast_init("root", OPERATOR_LIST);
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
static void set_parsing_ending_status(struct parser *parser, struct token *t)
{
    if (t->type == TOKEN_EOF)
        parser->state = PARSER_STATE_CONTINUE;
    else
    {
        warnx("error near unexpected token: `%s`",  t->value);
        parser->state = PARSER_STATE_FAILURE;
    }
}

static int parse_token(struct parser *parser, struct token *current,
        struct stack_elt *head)
{
    //if the symbol popped on the stack is a token...
    if (head->symbol->token_type != current->type)
    {
        set_parsing_ending_status(parser, current);
        stack_elt_free(head);
        return -1;
    }
    else if (token_type_is_value(current->type))
    {
        //get current word value into the ast
        if (head->ast->value)
            free(head->ast->value);
        head->ast->value = my_strdup(current->value);
    }
    stamp_continue(parser->input);
    return 0;
}

static int parse_rule(struct parser *parser, struct token *current,
        struct stack_elt *head)
{
    //if the symbol popped on the stack is a rule...
    struct symbol_array *arr = substitute_rule(
            head->symbol->rule_id, current->type, parser->table);
    if (!arr)
    {
        struct symbol_array *is_epsilon = substitute_rule(
            head->symbol->rule_id,
            parser->table->n_symbols - 1,
            parser->table);
        if (!is_epsilon)
        {
            set_parsing_ending_status(parser, current);
            stack_elt_free(head);
            //could not find correspondance in analysis table
            return -1;
        }
        else
        {
            //current top of stack rule is an epsilon rule, therefore
            //can be canceled.
            symbol_array_free(is_epsilon);
        }
    }
    else
    {
        stack_push_array(parser->stack, arr, head->ast);
    }
    return 0;
}

void parse(struct parser *parser, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct stamp *input = parser->input;
    struct stack *stack = parser->stack;
    while (!stamp_is_over(input))
    {
        struct token *current = stamp_read(input);
        struct stack_elt *head = stack_pop(stack);
        if (head->symbol->type == SYMBOL_TOKEN)
        {
            int try_parse_token = parse_token(parser, current, head);
            if (try_parse_token == -1)
                break;
        }
        else if (head->symbol->type == SYMBOL_RULE)
        {
            int try_parse_rule = parse_rule(parser, current, head);
            if (try_parse_rule == -1)
                return;
        }
        stack_elt_free(head);
    }
    if (parser->state != PARSER_STATE_FAILURE)
    {
        parser->state = stack->size == 0 ?
            PARSER_STATE_SUCCESS : PARSER_STATE_CONTINUE;
    }
    //post parsing treatment
    ast_clean(parser->ast);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[LL PARSER] done parsing. state: %d\n", parser->state);
    }
}
