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
    struct rule_array *rules = rule_array_init();
    //add all preconstructed rules here
    sh_rule_input(rules);
    sh_rule_and_or(rules);
    sh_rule_and_or_concat(rules);
    sh_rule_and_concat(rules);
    sh_rule_or_concat(rules);    
    sh_rule_and_linebreak(rules);
    sh_rule_or_linebreak(rules);
    sh_rule_pipeline(rules);
    sh_rule_pipe(rules);
    sh_rule_command(rules);    
    sh_rule_simple_command(rules);    
    sh_rule_shell_command(rules);
    sh_rule_redir_list(rules);
    sh_rule_redir(rules);
    sh_rule_redir_symbol(rules);
    sh_rule_redir_to(rules);
    sh_rule_ionumber(rules);
    sh_rule_element(rules);
    sh_rule_element_list(rules);
    sh_rule_arg_list(rules);
    sh_rule_list(rules);
    sh_rule_list_delim(rules);
    sh_rule_list_concat(rules);
    sh_rule_compound_list(rules);
    sh_rule_compound_list_delim(rules);
    sh_rule_compound_list_concat(rules);
    sh_rule_compound_list_break(rules);
    sh_rule_compound_list_break_delim(rules);
    sh_rule_compound_list_break_concat(rules);
    sh_rule_if(rules);
    sh_rule_else_concat(rules);
    return rules;
}
