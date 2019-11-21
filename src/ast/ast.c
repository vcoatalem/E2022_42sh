#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include "../execution/execution.h"

struct ast *ast_init(enum node_type type, char *value,
        enum operator_type op_type)
{
    struct ast *new_ast = malloc(sizeof(struct ast));

    if (new_ast == NULL)
        return NULL;

    new_ast->node_type = type;
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

struct ast *ast_dup(struct ast *ast)
{
    struct ast *dup = ast_init(ast->node_type, ast->value, ast->op_type);

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast *dup_child = ast_dup(ast->forest[i]);
        ast_add_child(dup, dup_child);
    }
    return dup;
}

void ast_free(struct ast *ast)
{
    if (!ast)
        return;
    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->forest[i]);
    if (ast->forest != NULL)
        free(ast->forest);
    if (ast->node_type == NODE_VALUE)
        free(ast->value);
    free(ast);
}

void ast_clean(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->node_type == NODE_OPERATOR
                && ast->forest[i]->nb_children == 0)
        {
            ast_free(ast->forest[i]);
            ast->nb_children--;
        }

        else
            ast_clean(ast->forest[i]);
    }
}

struct ast *get_child_of_name(struct ast *ast, const char *name)
{
    if (ast == NULL)
        return NULL;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->node_type == NODE_VALUE
                && !(strcmp(ast->forest[i]->value, name)))
        {
            return ast->forest[i];
        }
    }
    return NULL;
}

struct ast *find_op_type(struct ast *ast, enum operator_type op_type)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == op_type)
            return ast->forest[i];
    }

    return NULL;
}

char **get_arg_list(struct ast *ast)
{
    char **arg_list = NULL;
    size_t index = 0;
    while (ast->nb_children == 2)
    {
        struct ast *sub_list = get_child_of_name(ast, "arg_list");
        struct ast *element = get_child_of_name(ast, "element");
        //element contains one child; the value to be appended to list
        arg_list = realloc(arg_list, (index + 2) * sizeof(char *));
        arg_list[index] = element->forest[0]->value;
        arg_list[index + 1] = NULL;
        index++;
        ast = sub_list;
    }
    return arg_list;
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
