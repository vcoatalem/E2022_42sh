#include "parser.h"

struct grammar *g_grammar = NULL;

struct ast *parse(struct token_array *tokens)
{
    if (!g_grammar)
    {
        g_grammar = grammar_build();
    }
    struct test_runner *tr = test_runner_init(tokens, 0);
    tr->ast = ast_init(NODE_OPERATOR, NULL, OPERATOR_AND);

    int try_parse = rule_execute(RULE_INPUT, tr, g_grammar);
    if (try_parse == PARSE_FAILURE)
    {
        //free stuff
        return NULL;
    }
    else
    {
        struct ast *res = tr->ast;
        //free stuff
        return res;
    }
}
