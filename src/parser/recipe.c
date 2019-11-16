#include "parser.h"

static void test_execute_token_union(struct test *test,
        struct test_runner *runner)
{
    printf("[LOG] entered test_token_union\n");
    struct token_array *tok_union = test->props.token_union;
    if (runner->pos >= runner->token_array->size)
    {
        //reached the end of token_list. can't find anymore tokens
        runner->state = RUNNER_STATE_ERROR;
        return;
    }
    struct token *current = *(runner->token_array->tok_array + runner->pos);
    for (size_t i = 0; i < tok_union->size; i++)
    {
        if (current->type == (*(tok_union->tok_array + i))->type)
        {
            printf("[LOG] token_union success!\n");
            runner->pos++;
            return;
        }
    }
    //if no token was found, set error
    runner->state = RUNNER_STATE_ERROR;
    return;
}

static void test_execute_rule(struct test *test,
        struct test_runner *runner, struct grammar *grammar)
{
    rule_execute(test->props.rule_id, runner, grammar);
}

static void test_execute_sub_test(struct test *test,
        struct test_runner *runner, struct grammar *grammar)
{
    recipe_execute(test->props.sub_test, runner, grammar);
}

static void test_execute_value(struct test *test, struct test_runner *tr,
        struct grammar *grammar)
{
    switch(test->type)
    {
    case TEST_PARENT:
        test_execute_sub_test(test, tr, grammar);
        break;
    case TEST_TOKEN:
        test_execute_token_union(test, tr);
        break;
    case TEST_RULE:
        test_execute_rule(test, tr, grammar);
        break;
    default:
        break;
    }
}

// runner initialised by rule_execute
void recipe_execute(struct test *test, struct test_runner *runner,
        struct grammar *grammar)
{
    while (test)
    {
        if (test->optionnal) //reccursive call #0
        {
            //disjunction
            struct test_runner *disjunction_pass = test_runner_dup(runner);
            recipe_execute(test->next, disjunction_pass, grammar);
            if (disjunction_pass->state == RUNNER_STATE_SUCCESS)
            {
                //runner that passed this reached the end of the recipe
                test_runner_replace(&runner, disjunction_pass);
                return;
            }
            else
            {
                //it didnt
                test_runner_free(disjunction_pass);
            }
        }


        test_execute_value(test, runner, grammar); //actual test execution call
        if (runner->state != RUNNER_STATE_SUCCESS)
        {
            //current test execution failed
            return;
        }
        

        if (test->repeatable) //reccursive call #1
        {
            //disjunction test has already been run once above, trying to
            //run it again
            struct test_runner *disjunction_repeat = test_runner_dup(runner);
            recipe_execute(test, disjunction_repeat, grammar);
            if (disjunction_repeat->state == RUNNER_STATE_SUCCESS)
            {
                //runner that passed this reached the end of the recipe
                test_runner_replace(&runner, disjunction_repeat);
                return;
            }
            else
            {
                //it didnt
                test_runner_free(disjunction_repeat);
            }
        }
        test = test->next;
    }
    //reached the end of the recipe
    runner->state = RUNNER_STATE_SUCCESS;
}
