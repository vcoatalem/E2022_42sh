#include <err.h>
#include "execution.h"
#include "../main/42sh.h"
#include "../variables/variables.h"

struct command *command_init(char **args, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct command *cmd = calloc(1, sizeof(struct command));
    if (!args || !args[0] || !strcmp(args[0], ""))
    {
        cmd->type = COMMAND_NONE;
        return cmd;
    }
    cmd->args = args;
    for (size_t i = 0; args[i]; i++)
        cmd->n_args++;
    char *cmd_name = *(cmd->args);
    if (str_to_builtin(cmd_name))
    {
        cmd->type = COMMAND_BUILTIN;
    }
    else if (get_func(bundle->hash_table_func, cmd_name))
    {
        cmd->type = COMMAND_FUNCDEC;
    }
    else
    {
        cmd->type = COMMAND_SH;
    }
    return cmd;
}

struct command *shell_command_init(struct ast *ast)
{
    struct command *command = calloc(1, sizeof(struct command));
    command->ast = ast_dup(ast);
    command->type = COMMAND_AST;
    return command;
}

void command_free(struct command *command)
{
    if (!command)
        return;
    for (size_t i = 0; i < command->n_args; i++)
    {
        free(command->args[i]);
    }
    free(command->args);
    for (size_t i = 0; i < command->n_redirections; i++)
    {
        redirection_free(command->redirections[i]);
    }
    free(command->redirections);
    if (command->ast)
    {
        ast_free(command->ast);
    }
    free(command);
}

void command_add_redirection(struct command *command,
        struct redirection *redir)
{
    command->n_redirections++;
    command->redirections = realloc(command->redirections,
            sizeof(void*) * (command->n_redirections + 1));
    *(command->redirections + command->n_redirections - 1) = redir;
    *(command->redirections + command->n_redirections) = NULL;
}

static int command_execute_sh(struct command *command,
        void *bundle_ptr)
{
    if (!bundle_ptr)
        return 0;
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        ////child
        //execute command
        fflush(stdout);
        fflush(stderr);
        execvp(*(command->args), command->args);
        warnx("unknown command: %s", *(command->args));
        //if execution failed
        exit(RETURN_UNKNOWN_COMMAND);
    }
    waitpid(pid, &status, 0);
    return status % 255;
}

static int command_execute_builtin(struct command *command, void *bundle_ptr)
{
    //execute command
    builtin_handler handler = str_to_builtin(*(command->args));
    int execute_handler = handler(command->args, command->n_args,
            bundle_ptr);
    return execute_handler;
}

static int command_execute_funcdec(struct command *command, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct ast *func_ast = get_func(bundle->hash_table_func, *(command->args));
    int execute_funcdec = ast_execute(func_ast, bundle_ptr);
    return execute_funcdec;
}

int command_execute(struct command *command, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] entered command_execute\n");
    }
    int return_value = RETURN_UNKNOWN_COMMAND;
    command_apply_redirections(command, bundle_ptr);
    if (command->type == COMMAND_AST)
    {
        return_value = ast_execute(command->ast, bundle_ptr);
    }
    else if (command->type == COMMAND_SH)
    {
        return_value = command_execute_sh(command, bundle_ptr);
    }
    else if (command->type == COMMAND_BUILTIN)
    {
        return_value = command_execute_builtin(command, bundle_ptr);
    }
    else if (command->type == COMMAND_FUNCDEC)
    {
        return_value = command_execute_funcdec(command, bundle_ptr);
    }
    else //redirections without command
    {
        return_value = AST_SUCCESS;
    }
    command_restore_flux(command);
    if (command->invert_value)
    {
        return_value = return_value != AST_SUCCESS ? 0 : AST_ERROR;
    }
    if (bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] exiting command_execute with code: %d\n",
                return_value);
    }
    //set $? variable
    char el[8];
    sprintf(el, "%d", return_value);
    insert_variable(bundle->hash_table_var, "?", el);
    return return_value;
}
