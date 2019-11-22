#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_case(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;
#if 0
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_PATTERN)
        {
            struct ast *ast_pattern = ast->forest[i];
            // Pattern matching
            if (strcmp(ast_pattern->value, ast->value) == 0)
            {
                struct ast *ast_compound = find_op_type(ast_pattern,
                        OPERATOR_AND);
                return ast_execute(ast_compound, bundle_ptr);
            }
        }
    }
#endif
    return AST_ERROR;
}
