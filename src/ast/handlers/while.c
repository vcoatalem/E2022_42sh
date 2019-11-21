#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

static struct ast *find_op_while_body(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_WHILE_BODY)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_do(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_DO)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_done(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_DONE)
            return ast->forest[i];
    }

    return NULL;
}

int ast_handle_while(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    int try_execute = AST_SUCCESS;

    struct ast *ast_while_body = find_op_while_body(ast);
    struct ast *ast_do = find_op_do(ast);

    while (try_execute == AST_SUCCESS)
    {
        try_execute = ast_execute(ast_while_body, bundle_ptr);
        ast_execute(ast_do, bundle_ptr);
    }

    struct ast *ast_done = find_op_done(ast);
    return ast_execute(ast_done, bundle);
}
