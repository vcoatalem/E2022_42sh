#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

struct ast *ast_init(enum node_type type, char *value,
        enum operator_type op_type)
{
    struct ast *new_ast = malloc(sizeof(struct ast));

    if (new_ast == NULL)
        return NULL;
    if (type == NODE_OPERATOR)
    {
        new_ast->node_type = NODE_OPERATOR;
        new_ast->content.op_type = op_type;
    }
    else
    {
        new_ast->node_type = NODE_VALUE;

        if (value != NULL)
        {
            new_ast->content.value = calloc(1, strlen(value) + 1);
             strcpy(new_ast->content.value, value);
        }

        else
            new_ast->content.value = NULL;
    }
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
    struct ast *dup;

    if (ast->node_type == NODE_VALUE)
        dup = ast_init(NODE_VALUE, ast->content.value, OPERATOR_NONE);
    else
        dup = ast_init(NODE_OPERATOR, NULL, ast->content.op_type);
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
        free(ast->content.value);
    free(ast);
}

void ast_clean(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->nb_children == 1)
        {
            free(ast->forest[i]->forest[0]);
            free(ast->forest[i]);
            ast->nb_children--;
        }

        else
            ast_clean(ast->forest[i]);
    }
}

struct ast *get_child_of_name(struct ast *ast, const char *name)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->type == NODE_VALUE
                && !(strcmp(ast->forest[i]->content.value, name)))
        {
            return ast->forest[i];
        }
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
        arg_list[index] = ast->forest[j]->content.value;
        arg_list[index + 1] = NULL;
        index++;
        ast = sub_list;
    }
    return arg_list;
}


//do not use this for now, will need more work later on
//should initialise struct redirection[] (from execution/ module), not string[]
char **get_redir_list(struct ast *ast)
{
    char **redir_list = calloc(1, sizeof(char *));
    size_t index = 0;

    while (ast->nb_children == 2)
    {
        for (size_t i = 0; i < 2; i++)
        {
            if (strcmp(ast->forest[i]->content.value, "redir_list") == 0)
            {
                int j = i == 0 ? 1 : 0;
                redir_list[index] = ast->forest[j]->content.value;
                redir_list = realloc(arg_list, (index + 1) * sizeof(char *));
                index++;
                ast = ast->forest[i];
                break;
            }
        }
    }

    return redir_list;
}
