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
        struct ast *not_cmd = find_op_type(ast, OPERATOR_NOT);
        struct command *cmd = NULL;
        if (ast_cmd)
            cmd = ast_command_build(ast_cmd, bundle_ptr);
        else if (not_cmd)
        {
            //if we could not find a command child, this means this pipe
            //must have a node '!' as child
            cmd = ast_command_build(find_op_type(not_cmd, OPERATOR_COMMAND),
                    bundle_ptr);
            cmd->invert_value = 1;
        }
        pipe_add_command(pipe, cmd);
        ast = find_op_type(ast, OPERATOR_PIPE);
        if (ast)
        {
            //go on the pipe child of the pipeline node
            ast = find_op_type(ast, OPERATOR_PIPE);
        }
    }
    if (bundle->shopt->debug)
    {
        printf("[AST EXECUTION] built pipe; entering pipe execution\n");
    }
    int result = pipe_execute(pipe, bundle_ptr);
    if (bundle->shopt->debug)
    {
        printf("[AST EXECUTION] pipe execution returned: %d\n", result);
    }
    pipe_free(pipe);
    return result;
}
