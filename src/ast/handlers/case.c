#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

#if 0
commented this for compilation
static struct ast *find_op_compound(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_COMPOUND)
            return ast->forest[i];
    }
}
#endif

int ast_handle_case(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    if (ast == NULL)
        return AST_ERROR;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        #if 0
        commented this for compilation
        if (ast->forest[i]->op_type == OPERATOR_PATTERN)
        {
            struct ast *ast_pattern = ast->forest[i];
            // Pattern matching
            if (strcmp(ast_pattern->value, ast->value) == 0)
            {
                struct ast *ast_compound = find_op_compound(ast_pattern);
                return ast_execute(ast_compound);
            }
        }
        #endif
    }

    return AST_ERROR;
}
