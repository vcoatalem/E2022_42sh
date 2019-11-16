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
            runner->pos = runner->pos + 1;
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
    struct test_runner *disjunction_pass;
    struct test_runner *disjunction_repeat;
    if (test)
    {
        /**/printf("[LOG][%p] --- ENTERING recipe_execute:", (void*)runner);
        /**/test_print(test, 1, stdout);
        /**/printf("\n");
        /**/printf("[LOG][%p] RUNNER POS: %zu\n", (void*)runner, runner->pos);
    }
    if (!test)
    {
        //disjunction_pass reached the end of the recipe
        runner->state = RUNNER_STATE_SUCCESS;
    }
    while (test)
    {
        if (test_runner_is_over(runner))
        {
            //if runner does not have any more tokens to process, yet test
            //is not finished TODO: change error by unfinished to handle
            //multi line input
            runner->state = RUNNER_STATE_ERROR;
            return;
        }
        /**/printf("[LOG][%p] current test: ", (void*)runner);
        /**/test_print(test, 0, stdout);
        /**/printf("\n");
        if (test->optionnal) 
        {
            //if test is optionnal, dup a test_runner that will be
            //executed later on
            disjunction_pass = test_runner_dup(runner);
        }
        /**/printf("[LOG][%p] before execution pos: %zu\n", (void*)runner, runner->pos);
        test_execute_value(test, runner, grammar); //actual test execution call
        /**/printf("[LOG][%p] after execution pos: %zu\n", (void*)runner, runner->pos);
        if (runner->state == RUNNER_STATE_ERROR)
        {
            //current test execution failed
            return;
        }
        if (test->repeatable && !test_runner_is_over(runner))
        {
            //repeat disjunction should be run before pass
            printf("[LOG] test is repeatable; forking\n");
            //disjunction test has already been run once above, trying to
            //run it again
            disjunction_repeat = test_runner_dup(runner);
            recipe_execute(test, disjunction_repeat, grammar);
            if (disjunction_repeat->state == RUNNER_STATE_SUCCESS)
            {
                printf("[LOG] repeat disjunction success. pos: %zu\n", disjunction_repeat->pos);
                //runner that passed this reached the end of the recipe
                test_runner_replace(&runner, disjunction_repeat);
                return;
            }
            else
            {
                printf("[LOG] repeat disjunction failure\n");
                //it didnt
                test_runner_free(disjunction_repeat);
            }
        }
        if (test->optionnal) //reccursive call #2
        {
            //disjunction
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
        test = test->next;
    }
    printf("[LOG][%p] reached end of recipe with pos: %zu\n", (void*)runner, runner->pos);
    //reached the end of the recipe
    runner->state = RUNNER_STATE_SUCCESS;
}
