#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

#include "ast.h"
#include "../execution/execution.h"

struct ast *ast_init(char *value, enum operator_type op_type)
{
    struct ast *new_ast = malloc(sizeof(struct ast));

    if (new_ast == NULL)
        return NULL;

    new_ast->node_type = op_type != OPERATOR_NONE ? NODE_OPERATOR : NODE_VALUE;
    new_ast->op_type = op_type;

    if (value != NULL)
    {
        new_ast->value = calloc(1, strlen(value) + 1);
        strcpy(new_ast->value, value);
    }

    else
        new_ast->value = NULL;

    new_ast->forest = NULL;
    new_ast->nb_children = 0;
    return new_ast;
}

void ast_add_child(struct ast *ast, struct ast *child)
{
    if (!child)
        return;
    ast->nb_children += 1;
    ast->forest = realloc(ast->forest, ast->nb_children * sizeof(struct ast*));
    *(ast->forest + ast->nb_children - 1) = child;
}

//n points the index to be erased by left_shift procedure
static void left_shift(struct ast **ast, size_t n, size_t size)
{
    if (n > size - 1)
        return;
    for (size_t i = n; i < size ; i++)
    {
        ast[i] = ast[i + 1];
    }
}

void ast_remove_child(struct ast *ast, size_t n)
{
    if (!ast || ast->nb_children == 0 || n >= ast->nb_children)
        return;
    ast_free(ast->forest[n]);
    left_shift(ast->forest, n, ast->nb_children);
    ast->nb_children--;
    ast->forest = realloc(ast->forest,
            sizeof(ast->nb_children) * sizeof(void*));
}

void ast_free(struct ast *ast)
{
    if (!ast)
        return;
    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->forest[i]);
    if (ast->forest != NULL)
        free(ast->forest);
    if (ast->value)
        free(ast->value);
    free(ast);
}


static char *get_element_value(struct ast *ast)
{
    struct ast *element_ast = find_op_type(ast, OPERATOR_GET_VALUE);

    if (element_ast == NULL)
        return NULL;

    return element_ast->forest[0]->value;
}

char **get_arg_list(struct ast *ast)
{
    char **arg_list = NULL;
    size_t index = 0;

    while (ast != NULL)
    {
        struct ast *element_list = find_op_type(ast, OPERATOR_ARG_LIST);
        arg_list = realloc(arg_list, (index + 2) * sizeof(char *));
        arg_list[index] = get_element_value(ast);
        arg_list[index + 1] = NULL;
        index++;
        ast = element_list;
    }

    return arg_list;
}

struct command *get_command(struct ast *ast)
{
    struct ast *simple_cmd = find_op_type(ast, OPERATOR_COMMAND);

    if (simple_cmd != NULL)
    {
        struct ast *args = find_op_type(simple_cmd, OPERATOR_ARG_LIST);
        //struct ast *redir_list = find_op_type(simple_cmd, OPERATOR_REDIR_LIST);

        char **arg_list = get_arg_list(args);
        // TODO: Add get redirection_list function
        //struct redirection **redirs = get_redirs(redir_list);

        struct command *cmd = command_init(arg_list, NULL);

        return cmd;
    }

    return NULL;
}

//do not use this for now, will need more work later on
//should initialise struct redirection[] (from execution/ module), not string[]

#if 0
struct redirection **get_redirections(struct ast *ast)
{
    struct redirection **redir_list = NULL;
    size_t index = 0;

    while (ast->nb_children == 2)
    {
        struct ast *sub_list = get_child_of_name(ast, "redir_list");
        struct ast *redirection = get_child_of_name(ast, "redir");
    }
}

char **get_redir_list(struct ast *ast)
{
    char **redir_list = calloc(1, sizeof(char *));
    size_t index = 0;

    while (ast->nb_children == 2)
    {
        for (size_t i = 0; i < 2; i++)
        {
            if (strcmp(ast->forest[i]->value, "redir_list") == 0)
            {
                int j = i == 0 ? 1 : 0;
                redir_list[index] = ast->forest[j]->value;
                redir_list = realloc(arg_list, (index + 1) * sizeof(char *));
                index++;
                ast = ast->forest[i];
                break;
            }
        }
    }

    return redir_list;
}
#endif
