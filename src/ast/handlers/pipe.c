#include "../ast.h"
#include "../../execution/execution.h"

#define MAX_ARGS_COUNT 2048
#define MAX_REDIR_COUNT 64


int ast_handle_pipe(struct ast *ast)
{
    struct pipe *pipe = pipe_init();
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast *cmd_ast = *(ast->forest + i);
        char *args[MAX_ARGS_COUNT] = { NULL };
        struct ast *args_ast = *(cmd_ast->forest);
        for (size_t j = 0; j < args_ast->nb_children; j++)
        {
            args[j] = (*(args_ast->forest + j))->content.value;
        }
        struct ast *redir_ast = *(cmd_ast->forest + 1);
        if (!redir_ast)
            break;
        //handle redirections later on

        struct command *cmd = command_init(args, NULL);
        pipe_add_command(pipe, cmd);
    }
    return pipe_execute(pipe);
}
