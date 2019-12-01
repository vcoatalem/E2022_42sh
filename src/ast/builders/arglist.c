#include "../ast.h"

static void arg_list_get_arg(char ***arg_list, size_t *index, struct ast *ast)
{

    *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
    (*arg_list)[*index] = strdup(ast->forest[0]->value);
    (*arg_list)[*index + 1] = NULL;
    *index = *index + 1;
}

static void arg_list_get_expand_arg(char ***arg_list, size_t *index,
                                            struct ast *ast)
{
    char **expanded_args = expand_file_pattern(ast->forest[0]->value);
    if (!expanded_args)
    {
        *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
        (*arg_list)[*index] = strdup(ast->forest[0]->value);
        //printf("%zu: %s\n", *index, (*arg_list)[*index]);
        *index = *index + 1;
    }
    else
    {
        for (size_t i = 0; *(expanded_args + i); i++)
        {
            *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
            (*arg_list)[*index] = strdup(expanded_args[i]);
            //printf("%zu: %s\n", *index, (*arg_list)[*index]);
            *index = *index + 1;
        }
        (*arg_list)[*index] = NULL;
        free(expanded_args);
    }
}

static void arg_list_get_subshell(char ***arg_list, size_t *index,
                                        struct ast *ast, void *bundle_ptr)
{
    char *substitute = substitute_shell(ast->forest[0]->value);
    //split substitute using IFS
    if (!substitute)
        return;
    if (!*substitute)
    {
        free(substitute);
        return;
    }
    char **fields = split_fields(substitute, bundle_ptr);
    free(substitute);
    if (fields)
    {
        for (size_t i = 0; fields[i]; i++)
        {
            *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
            (*arg_list)[*index] = fields[i];
            (*arg_list)[*index + 1] = NULL;
            *index = *index + 1;
        }
    }
    free(fields);
}

static void arg_list_get_arithmetic_value(char ***arg_list, size_t *index,
                                            struct ast *ast)
{
    *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
    //TODO: implement arithmetic expression substitution
    (*arg_list)[*index] = substitute_shell(ast->forest[0]->value);
    (*arg_list)[*index + 1] = NULL;
    *index = *index + 1;
}

char **ast_arg_list_build(struct ast *ast, void *bundle_ptr)
{
    char **arg_list = NULL;
    size_t index = 0;

    while (ast != NULL)
    {
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
            arg_list_get_subshell(&arg_list, &index, sub_value, bundle_ptr);
        }
        else if (arithmetic_value)
        {
            arg_list_get_arithmetic_value(&arg_list, &index, sub_value);
        }
        else
        {
            arg_list_get_arg(&arg_list, &index, value);
        }
        ast = element_list;
    }

    return arg_list;
}
