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


void rule_execute(enum rule_id id, struct test_runner *parent,
        struct grammar *grammar)
{
    printf("[LOG] entered rule_execute for id %d\n", id);
    struct rule *rule = *(grammar->rules + id);
    if (!rule)
    {
        printf("[LOG] specified rule not found\n");
        return;
    }
    for (size_t i = 0; i < rule->n_recipes; i++)
    {
        printf("[LOG] entered recipe #%zu / %zu\n", i, rule->n_recipes - 1);
        struct test_runner *dup = test_runner_fork(parent);
        enum operator_type ast_type = rule_ast_command(id);
        dup->ast = ast_init(
            ast_type == OPERATOR_NONE ? NODE_VALUE : NODE_OPERATOR,
            ast_type == OPERATOR_NONE ? "" : NULL,
            ast_type);
        recipe_execute(*(rule->recipes + i), dup, grammar);
        if (dup->state == RUNNER_STATE_SUCCESS)
        {
            printf("[LOG] successfully executed rule %d\n", id);
            //if the recipe was runned successfully, set the parent pos to
            //the pos of the successful test_runner
            ast_add_child(parent->ast, dup->ast);
            parent->pos = dup->pos;
            test_runner_free(dup);
            return;
        }
        test_runner_free(dup);
    }
    printf("[LOG] could not execute rule #%d\n", id);
    parent->state = RUNNER_STATE_ERROR;
}

void rule_print(struct rule *rule, FILE *out)
{
    printf("--- RULE:\n");
    for (size_t i = 0; i < rule->n_recipes; i++)
    {
        fprintf(out, "recipe #%zu: ", i);
        test_print(*(rule->recipes + i), 1, out);
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
