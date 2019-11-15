#include "../ast.h"
#include "../../execution/execution.h"

int ast_handle_for(struct ast *ast)
{
    return ast_handle_while(ast);
}
