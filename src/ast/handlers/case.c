#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

static struct *find_op_compound(struct ast *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->forest[i]->op_type == OPERATOR_COMPOUND)
            return ast->forest[i];
    }
}

int ast_handle_case(struct ast *ast, struct execution_bundle *bundle)
{
    if (!bundle)
        break;

    if (ast == NULL)
        return AST_ERROR;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
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
    }

    return AST_ERROR;
}
