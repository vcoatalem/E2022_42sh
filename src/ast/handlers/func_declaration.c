#include "../ast.h"
#include "../../main/42sh.h"
#include "../../hashtable/hashtablefunc.h"

int ast_handle_func_declaration(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;

    struct ast *ast_func_name = find_op_type(ast, OPERATOR_GET_VALUE);
    struct ast *ast_func_body = find_op_type(ast, OPERATOR_AND);

    if (ast_func_name == NULL || ast_func_body == NULL)
        return AST_ERROR;

    insert_func(bundle->hash_table_func, ast_func_name->value,
            ast_func_body);

    return AST_SUCCESS;
}
