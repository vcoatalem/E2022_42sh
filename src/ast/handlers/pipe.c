#include "../ast.h"
#include "../../main/42sh.h"
#include "../../execution/execution.h"
#include "string.h"

#define MAX_ARGS_COUNT 2048
#define MAX_REDIR_COUNT 64

int ast_handle_pipe(struct ast *ast, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return AST_ERROR;

    struct pipe *pipe = pipe_init();

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast *cmd_ast = get_child_of_name(ast, "cmd");
        struct ast *args_ast = get_child_of_name(cmd_ast, "argv");
        char *args[MAX_ARGS_COUNT] = { NULL };

        for (size_t j = 0; j < args_ast->nb_children; j++)
        {
            args[j] = (*(args_ast->forest + j))->value;
        }

        struct ast *redir_ast = get_child_of_name(cmd_ast, "redir");
        if (!redir_ast)
            break;
        //handle redirections later on

        struct command *cmd = command_init(args, NULL);
        pipe_add_command(pipe, cmd);
    }
    int result = pipe_execute(pipe);
    pipe_free(pipe);
    return result;
}
