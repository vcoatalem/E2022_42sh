#include "parser.h"

struct ast *parse(struct token_array *tokens, struct grammar *grammar)
{
    struct test_runner *tr = test_runner_init(tokens, 0);
    
    //rule_execute(RULE_INPUT, tr, grammar);
    rule_execute(RULE_SIMPLE_COMMAND, tr, grammar);
    if (tr->state == RUNNER_STATE_SUCCESS)
    {
        if (tr->pos >= tr->token_array->size)
        {
            printf("parse: rule_execute returned success but do not \
                use the entire token_array\n");
            return NULL;
        }
        printf("parse: valid input; returning ast\n");
        return tr->ast;
    }
    else
    {
        printf("parse: invalid input\n");
        //handle more cases
        return NULL;
    }
}
