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
        struct command *cmd = ast_command_build(ast_cmd, bundle_ptr);
        printf("adding command to pipe\n");
        pipe_add_command(pipe, cmd);
        ast = find_op_type(ast, OPERATOR_PIPE);
        if (ast)
        {
            //go on the pipe child of the pipeline node
            ast = find_op_type(ast, OPERATOR_PIPE);
        }
    }

    int result = pipe_execute(pipe, bundle_ptr);
    pipe_free(pipe);
    return result;
}
