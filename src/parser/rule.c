#include "parser.h"

static enum command_type rule_ast_command(enum rule_id id)
{
    switch (id)
    {
        case RULE_NONE:
            return OPERATOR_AND;
        case RULE_INPUT:
            return OPERATOR_AND;
        case RULE_LIST:
            return OPERATOR_AND;
        case RULE_AND_OR:
            return OPERATOR_AND;
        case RULE_AND:
            return OPERATOR_AND;
        case RULE_OR:
            return OPERATOR_OR;
        case RULE_PIPELINE:
            return OPERATOR_PIPE;
        case RULE_SIMPLE_COMMAND:
            return OPERATOR_CMD;
        case RULE_REDIRECTION:
            return OPERATOR_NONE;
        case RULE_ELEMENT:
            return OPERATOR_NONE;
        default:
            return OPERATOR_NONE;
    }
}

int rule_execute(enum rule_id id, struct test_runner *parent,
        struct grammar *grammar)
{
    struct rule *rule = *(grammar->rules + id);
    for (size_t i = 0; i < rule->n_recipes; i++)
    {
        struct test_runner *dup = test_runner_dup(parent);
        dup->ast = ast_init(rule_ast_command(id));
        //initialise ast
        struct test *test = *(rule->recipes + i);
        while (test)
        {
            int try_execute = test_execute(test, dup, grammar);
            if (try_execute == PARSE_FAILURE)
            {
                //free ressources
                continue;
            }
            test = test->next;
        }
        //whenever a receipe success, immediatly return it. ?

        //append built ast to parent

        //update parent position to match this one. ?
        return PARSE_SUCCESS;
    }
    return PARSE_FAILURE;
}
