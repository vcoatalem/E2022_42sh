#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"

static void set_variable_name_value(char *str, char *varname, char *varvalue)
{
    size_t it = 0;
    size_t name_it = 0;
    size_t val_it = 0;
    int parsing_state = 0;
    while (*(str + it))
    {
        if (*(str + it) == '=')
        {
            parsing_state = 1;
        }
        else
        {
            if (parsing_state == 0)
            {
                *(varname + name_it) = *(str + it);
                name_it++;
            }
            else
            {
                *(varvalue + val_it) = *(str + it);
                val_it++;
            }
        }
        it++;
    }
}

int ast_handle_vardec(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle || !bundle->hash_table_var)
        return AST_ERROR;

    if (ast == NULL || ast->nb_children == 0)
        return AST_ERROR;
    char buffer_name[2048] = { 0 };
    char buffer_value[2048] = { 0 };
    set_variable_name_value(ast->forest[0]->value, buffer_name, buffer_value);
    insert_variable(bundle->hash_table_var, buffer_name, buffer_value);
    return AST_SUCCESS;
}
