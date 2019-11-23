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
