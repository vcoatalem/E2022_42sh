#include "parser.h"

struct rule *rule_init(void)
{
    struct rule *res = calloc(1, sizeof(struct rule));
    res->recipes = NULL;
    res->n_recipes = 0;
    return res;
}

void rule_free(struct rule *rule)
{
    for (size_t i = 0; i < rule->n_recipes; i++)
    {
        test_free(*(rule->recipes + i));
    }
    free(rule);
}

static enum operator_type rule_ast_command(enum rule_id id)
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
        enum operator_type ast_type = rule_ast_command(id);
        dup->ast = ast_init(
            ast_type == OPERATOR_NONE ? NODE_VALUE : NODE_OPERATOR,
            ast_type == OPERATOR_NONE ? "" : NULL,
            ast_type);
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
        //append built ast to parent
        ast_add_child(parent->ast, ast_dup(dup->ast));

        //update parent position to match this one. ?
        
        //free dup
        return PARSE_SUCCESS;
    }
    return PARSE_FAILURE;
}

void rule_print(struct rule *rule, FILE *out)
{
    printf("--- RULE:\n");
    for (size_t i = 0; i < rule->n_recipes; i++)
    {
        fprintf(out, "recipe #%zu: ", i);
        test_print(*(rule->recipes + i), out);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

void rule_add_test(struct rule *rule, struct test *test)
{
    rule->n_recipes++;
    rule->recipes = realloc(rule->recipes, sizeof(void*) * rule->n_recipes);
    *(rule->recipes + rule->n_recipes - 1) = test;
}
