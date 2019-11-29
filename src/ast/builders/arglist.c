#include "../ast.h"

static void arg_list_get_arg(char **arg_list, size_t *index, struct ast *ast)
{
    arg_list[*index] = ast->forest[0]->value;
    arg_list[*index + 1] = NULL;
    *index = *index + 1;
}

static void arg_list_get_expand_arg(char ***arg_list, size_t *index,
                                            struct ast *ast)
{
    char **expanded_args = NULL;
    size_t n_args = 0;
    get_find(ast->forest[0]->value, "./",
            &expanded_args, &n_args);
    //printf("n_args: %zu\n", n_args);
    for (size_t i = 0; i < n_args; i++)
    {
        *arg_list = realloc(*arg_list, (*index + 3) * sizeof(char *));
        (*arg_list)[*index] = expanded_args[i];
        *index = *index + 1;
    }
    *arg_list[*index] = NULL;
    if (expanded_args)
        free(expanded_args);
}

static void arg_list_get_subshell(char **arg_list, size_t *index,
                                            struct ast *ast)
{
    arg_list[*index] = substitute_shell(ast->forest[0]->value);
    arg_list[*index + 1] = NULL;
    *index = *index + 1;
}

static void arg_list_get_arithmetic_value(char **arg_list, size_t *index,
                                            struct ast *ast)
{
    //TODO: implement arithmetic expression substitution
    arg_list[*index] = substitute_shell(ast->forest[0]->value);
    arg_list[*index + 1] = NULL;
    *index = *index + 1;
}

char **ast_arg_list_build(struct ast *ast)
{
    char **arg_list = NULL;
    size_t index = 0;

    while (ast != NULL)
    {
        arg_list = realloc(arg_list, (index + 2) * sizeof(char *));
        struct ast *element_list = find_op_type(ast, OPERATOR_ARG_LIST);
        struct ast *value = find_op_type(ast, OPERATOR_GET_VALUE);
        struct ast *expand_value = find_op_type(value,
                OPERATOR_GET_EXPAND_VALUE);
        struct ast *sub_value = find_op_type(value,
                OPERATOR_GET_SUBSHELL_VALUE);
        struct ast *arithmetic_value = find_op_type(value,
                OPERATOR_GET_ARITHMETIC_VALUE);
        if (expand_value)
        {
            arg_list_get_expand_arg(&arg_list, &index, expand_value);
        }
        else if (sub_value)
        {
            arg_list_get_subshell(arg_list, &index, sub_value);
        }
        else if (arithmetic_value)
        {
            arg_list_get_arithmetic_value(arg_list, &index, sub_value);
        }
        else
        {
            arg_list_get_arg(arg_list, &index, value);
        }
        ast = element_list;
    }

    return arg_list;
}
