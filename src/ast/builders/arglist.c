#include "../main/42sh.h"
#include "../ast.h"
#include "../../variables/variables.h"

//substitution function for args of type WORD_EXPAND
static void arg_list_get_expand_arg(char ***arg_list, size_t *index,
                                            struct ast *ast, void *bundle_ptr)
{
    char **expanded_args = expand_file_pattern(ast->forest[0]->value,
            bundle_ptr);
    if (!expanded_args)
    {
        *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
        (*arg_list)[*index] = strdup(ast->forest[0]->value);
        //printf("%zu: %s\n", *index, (*arg_list)[*index]);
        *index = *index + 1;
    }
    else
    {
        for (size_t i = 0; expanded_args[i]; i++)
        {
            *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
            (*arg_list)[*index] = strdup(expanded_args[i]);
            free(expanded_args[i]);
            *index = *index + 1;
        }
        free(expanded_args);
    }
    (*arg_list)[*index] = NULL;
}

//substitution function for tokens of type TOKEN_SUBSHELL
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

//substitution function for tokens of type TOKEN_ARITHMETIC
static void arg_list_get_arithmetic_value(char ***arg_list, size_t *index,
                                            struct ast *ast)
{
    *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
    //TODO: implement arithmetic expression substitution
    (*arg_list)[*index] = substitute_shell(ast->forest[0]->value);
    (*arg_list)[*index + 1] = NULL;
    *index = *index + 1;
}

//utility function: split str in space-separated (IFS?) words
static char **str_split_spaces(char *str, size_t *n_words)
{
    char **argv = NULL;
    char *save_ptr;
    char *token;
    int first = 1;
    while (1)
    {
        token = strtok_r(first ? str : NULL, " ", &save_ptr);
        first = 0;
        if (!token)
            break;
        *n_words = *n_words + 1;
        argv = realloc(argv, (*n_words + 1) * sizeof(char*));
        *(argv + *n_words - 1) = strdup(token);
        *(argv + *n_words) = NULL;
    }
    return argv;
}

//substitution function for tokens of type TOKEN_WORD_NO_SUBSTITUTION
//(just adds the value)
static void arg_list_get_arg(char ***arg_list, size_t *index, struct ast *ast)
{
    *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
    (*arg_list)[*index] = strdup(ast->forest[0]->value);
    //TODO: substitution goes there
    (*arg_list)[*index + 1] = NULL;
    *index = *index + 1;
}

static void arg_list_get_substituted_arg(char ***arg_list, size_t *index,
        struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    char *substituted = var_substitute(ast->forest[0]->value,
            bundle->hash_table_var);
    if (bundle && bundle->shopt->debug)
    {
        printf("[COMMAND BUILDING] applied substitution on '%s' --> '%s'\n",
                ast->forest[0]->value, substituted);
    }
    if (strcmp(substituted, ast->forest[0]->value))
    {
        //if a substitution did happen, we split the resulting string
        //in space separated words
        size_t n_words = 0;
        char **words = str_split_spaces(substituted, &n_words);
        for (size_t i = 0; i < n_words; i++)
        {
            *arg_list = realloc(*arg_list, (*index + 2) * sizeof(char *));
            (*arg_list)[*index] = words[i];
            (*arg_list)[*index + 1] = NULL;
            *index = *index + 1;
        }
        free(words);
    }
    else
    {
        //if no substitution happened, we simply treat current token as if it
        //was a TOKEN_WORD_NO_SUBSTITUTION
        arg_list_get_arg(arg_list, index, ast);
    }
    free(substituted);
}

//according to the type of the node, will call a different builder to extract
//the value from the node or its child(ren)
char **ast_arg_list_build(struct ast *ast, void *bundle_ptr)
{
    char **arg_list = NULL;
    size_t index = 0;
    struct execution_bundle *bundle = bundle_ptr;
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
        struct ast *no_substitution_value = find_op_type(value,
                OPERATOR_GET_NO_SUBSTITUTION_VALUE);
        if (expand_value)
        {
            arg_list_get_expand_arg(&arg_list, &index, expand_value,
                    bundle_ptr);
        }
        else if (sub_value)
        {
            arg_list_get_subshell(&arg_list, &index, sub_value, bundle_ptr);
        }
        else if (arithmetic_value)
        {
            arg_list_get_arithmetic_value(&arg_list, &index, sub_value);
        }
        else if (no_substitution_value)
        {
            arg_list_get_arg(&arg_list, &index, value);
        }
        else //if (value)
        {
            arg_list_get_substituted_arg(&arg_list, &index, value, bundle_ptr);
        }
        ast = element_list;
    }
    if (bundle && bundle->shopt->debug)                 
    {                                                   
        printf("[COMMAND BUILDING] built arg list: "); 
        for (size_t i = 0; arg_list[i]; i++)            
        {                                               
            printf(" `%s`,", arg_list[i]);              
        }                                               
        printf("\n");                                   
    }                                                   
    return arg_list;
}
