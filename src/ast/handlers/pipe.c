#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"
#include "string.h"

int ast_handle_pipe(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    struct pipe *pipe = pipe_init();

    while (ast != NULL)
    {
        struct ast *ast_cmd = find_op_type(ast, OPERATOR_COMMAND);
        struct command *cmd = get_command(ast_cmd);

        pipe_add_command(pipe, cmd);
        ast = find_op_type(ast, OPERATOR_PIPE);
    }

    int result = pipe_execute(pipe);
    pipe_free(pipe);
    return result;
}
