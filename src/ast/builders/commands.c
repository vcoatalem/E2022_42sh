#include "../ast.h"

static struct command *ast_simple_command_build(struct ast *ast,
        void *bundle_ptr)
{
    struct ast *args = find_op_type(ast, OPERATOR_ARG_LIST);
    struct ast *redir_list = find_op_type(ast, OPERATOR_REDIR_LIST);

    char **arg_list = ast_arg_list_build(args, bundle_ptr);
    struct redirection **redirs = ast_redirection_list_build(redir_list);

    struct command *cmd = command_init(arg_list, bundle_ptr);
    if (redirs)
    {
        size_t n_redirs = 0;
        while (*(redirs + n_redirs))
        {
            command_add_redirection(cmd, *(redirs + n_redirs));
            n_redirs++;
        }
        free(redirs);
    }
    //free arglist 
    if (arg_list)
    {
        for (size_t i = 0; *(arg_list + i); i++)
            free(arg_list[i]);
        free(arg_list);
    }
    //free redirlist
    return cmd;
}

static struct command *ast_shell_command_build(struct ast *ast)
{
    struct ast *shell_cmd = find_op_type(ast, OPERATOR_SHELL_COMMAND);
    struct ast *redir_list = find_op_type(ast, OPERATOR_REDIR_LIST);
    struct redirection **redirs = ast_redirection_list_build(redir_list);
    struct command *cmd = shell_command_init(shell_cmd->forest[0]);
    if (redirs)
    {
        size_t n_redirs = 0;
        while (*(redirs + n_redirs))
        {
            command_add_redirection(cmd, *(redirs + n_redirs));
            n_redirs++;
        }
        free(redirs);
    }
    return cmd;
}

struct command *ast_command_build(struct ast *ast, void *bundle_ptr)
{
    struct ast *simple_cmd = find_op_type(ast, OPERATOR_COMMAND);
    if (simple_cmd != NULL)
    {
        return ast_simple_command_build(simple_cmd, bundle_ptr);
    }
    struct ast *shell_cmd = find_op_type(ast, OPERATOR_SHELL_COMMAND);
    if (shell_cmd != NULL)
    {
        //in the case of a shell command, the redirection ast is connected to
        //the command ast (not the shell command ast) hence we pass
        //ast (not shell_cmd)
        return ast_shell_command_build(ast);
    }
    return NULL;
}
