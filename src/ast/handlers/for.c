#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

int ast_handle_for(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;

    int return_execute = AST_SUCCESS;

    struct ast *ast_for_element = find_op_type(ast, OPERATOR_GET_VALUE);
    char *element_name = ast_for_element->forest[0]->value;

    struct ast *ast_for_clause = find_op_type(ast, OPERATOR_ARG_LIST);
    struct ast *ast_do = find_op_type(ast, OPERATOR_DO);
    struct ast *ast_do_list = find_op_type(ast_do, OPERATOR_LIST);

    if (!ast_for_clause || !ast_do)
        return AST_SUCCESS;

    struct ast *ast_for_element_list = find_op_type(ast_for_clause,
                OPERATOR_ARG_LIST);
    char **args = ast_arg_list_build(ast_for_element_list, bundle_ptr);
    bundle->ast_traversal_context.loop_depth++;
    for (size_t i = 0; args[i]; i++)
    {
        insert_variable(bundle->hash_table_var, element_name, args[i]);
        return_execute = ast_execute(ast_do_list, bundle);
        if (return_execute == AST_SUCCESS)
        {
            //loop break/continue handlers
            if (bundle->ast_traversal_context.found_break)
            {
                bundle->ast_traversal_context.found_break = 0;
                break;
            }
            if (bundle->ast_traversal_context.found_continue)
            {
                bundle->ast_traversal_context.found_continue = 0;
                continue;
            }
        }
        else
            break;
    }
    for (size_t i = 0; args[i]; i++)
        free(args[i]);
    free(args);
    bundle->ast_traversal_context.loop_depth--;
    return return_execute;
}
