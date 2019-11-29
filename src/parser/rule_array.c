#include "parser.h"

static struct rule_array *rule_array_init(void)
{
    struct rule_array *rules = calloc(1, sizeof(struct rule_array));
    rules->capacity = 4;
    rules->size = 0;
    rules->rules = calloc(1, sizeof(void*) * rules->capacity);
    return rules;
}

// function initialising all the rules
void rule_array_add(struct rule_array *array, struct rule *r)
{
    array->size = array->size + 1;
    if (array->capacity == array->size)
    {
        array->capacity *= 2;
        array->rules = realloc(array->rules, sizeof(void*)
                * array->capacity);
    }
    array->rules[array->size - 1] = r;
}

void rule_array_free(struct rule_array *array)
{
    for (size_t i = 0; i < array->size; i++)
    {
        rule_free(array->rules[i]);
    }
    free(array->rules);
    free(array);
}

//this function builds the whole predetermined rule list
struct rule_array *rule_array_build(void)
{
    //TODO: merge rule functions in sub categories
    struct rule_array *rules = rule_array_init();
    //add all preconstructed rules here

    sh_rule_element_groups            (rules);
    sh_rule_command_groups            (rules);
    sh_rule_redir_groups              (rules);
    sh_rule_pipe_groups               (rules);
    sh_rule_input                     (rules);
    sh_rule_and_or_groups             (rules);
    sh_rule_list_groups               (rules);
    sh_rule_compound_list_groups      (rules);
    sh_rule_compound_list_break_groups(rules);
    sh_rule_do_groups                 (rules);
    sh_rule_funcdec_groups            (rules);
    sh_rule_if_groups                 (rules);
    sh_rule_misc                      (rules);
    sh_rule_case_groups              (rules);
    return rules;
}
