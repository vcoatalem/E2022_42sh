#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

static struct ast *find_op_if_body(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_IF_BODY)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_then(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_THEN)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_else(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_ELSE)
            return ast->forest[i];
    }

    return NULL;
}

int ast_handle_if(struct ast *ast, struct execution_bundle *bundle)
{
    if (!bundle)
        break;

    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;

    struct ast *ast_if_body = find_op_if_body(ast);
    struct ast *ast_then = find_op_then(ast);
    if (ast_if_body == NULL || ast_then == NULL)
        return AST_ERROR;

    if (ast_execute(ast_if_body) == AST_SUCCESS)
        return ast_execute(ast_then);

    else
    {
        struct ast *ast_else = find_op_else(ast);
        if (ast_else == NULL)
            return AST_ERROR;

        return ast_execute(ast_else);
    }
}
