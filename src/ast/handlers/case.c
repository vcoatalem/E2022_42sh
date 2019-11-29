#include <fnmatch.h>

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
    
    struct ast *val_a = find_op_type(ast, OPERATOR_GET_VALUE);
    struct ast *clause = find_op_type(ast, OPERATOR_CASE);
    while (clause && clause->nb_children > 1)
    {
        //while clause is not ESAC...
        struct ast *item = find_op_type(clause, OPERATOR_GET_VALUE);
        struct ast *val_b = find_op_type(item, OPERATOR_GET_VALUE);
        struct ast *list = find_op_type(item, OPERATOR_LIST);
        if (fnmatch(val_a->forest[0]->value,
                    val_b->forest[0]->value,
                    0) == 0)
        {
            return ast_execute(list, bundle_ptr);
        }
        clause = find_op_type(clause, OPERATOR_CASE);
    }
    return AST_SUCCESS;
}
