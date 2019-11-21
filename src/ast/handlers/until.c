#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

static struct ast *find_op_until_body(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_UNTIL_BODY)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_do(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_DO)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_done(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->content.op_type == OPERATOR_DONE)
            return ast->forest[i];
    }

    return NULL;
}

int ast_handle_until(struct ast *ast, struct execution_bundle *bundle)
{
    if (!bundle)
        break;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_ERROR;

    struct ast *ast_until_body = find_op_until_body(ast);
    struct ast *ast_do = find_op_do(ast);

    while (try_execute == AST_ERROR)
    {
        try_execute = ast_execute(ast_until_body);
        ast_execute(ast_do);
    }

    struct ast *ast_done = find_op_done(ast);
    return ast_execute(ast_done);
}
