#include "../ast.h"
#include "../../main/42sh.h"
#include "../../hashtable/hashtablefunc.h"

static struct ast *find_op_function_name(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_FUNC_NAME)
            return ast->forest[i];
    }

    return NULL;
}

static struct ast *find_op_function_body(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_FUNC_BODY)
            return ast->forest[i];
    }

    return NULL;
}

int ast_handle_func_declaration(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;

    struct ast *ast_func_name = find_op_function_name(ast);
    struct ast *ast_func_body = find_op_function_body(ast);

    if (ast_func_name == NULL || ast_func_body == NULL)
        return AST_ERROR;

    insert_func(bundle->hash_table_func, ast_func_name->value,
            ast_func_body);

    return AST_SUCCESS;
}
