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
        err(errno, "ERROR_AST_INIT: Cannot allocate memory.");

    if (type == NODE_OPERATOR)
    {
        new_ast->node_type = NODE_OPERATOR;
        new_ast->content.op_type = op_type;
    }

    else
    {
        new_ast->node_type = NODE_VALUE;
        new_ast->content.value = calloc(1, strlen(value) + 1);
        strcpy(new_ast->content.value, value);
    }

    new_ast->forest = NULL;
    new_ast->nb_children = 0;

    return new_ast;
}

void ast_add_child(struct ast *ast, struct ast *child)
{
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
    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->forest[i]);

    if (ast->forest != NULL)
        free(ast->forest);
    if (ast->node_type == NODE_VALUE)
        free(ast->content.value);
    free(ast);
}

// =============
// AST EXECUTION
// =============

int ast_handle_and(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i]) == AST_ERROR)
            return AST_ERROR;
    }

    return AST_SUCCESS;
}

int ast_handle_or(struct ast *ast)
{
    if (ast == NULL)
        return AST_ERROR;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast_execute(ast->forest[i]) == AST_SUCCESS)
            return AST_SUCCESS;
    }

    return AST_ERROR;
}

int ast_handle_cmd(struct ast *ast);
int ast_handle_pipe(struct ast *ast);

ast_handler get_handler(enum operator_type type)
{
    if (type == OPERATOR_CMD)
        return &ast_handle_cmd;

    else if (type == OPERATOR_AND)
        return &ast_handle_and;

    else if (type == OPERATOR_OR)
        return &ast_handle_or;

    else if (type == OPERATOR_PIPE)
         return &ast_handle_pipe;

    else
        return NULL;
}

int ast_execute(struct ast *ast);
