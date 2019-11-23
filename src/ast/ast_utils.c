#include <string.h>
#include <stdio.h>

#include "ast.h"

void ast_clean(struct ast *ast)
{
    if (!ast)
        return;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        ast_clean(ast->forest[i]);
        if (ast->forest[i]->op_type != OPERATOR_NONE
                && ast->forest[i]->nb_children == 0)
        {
            ast_remove_child(ast, i);
            i--;
        }
    }
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
