#include <err.h>
#include "execution.h"
#include "../main/42sh.h"
#include "../variables/variables.h"

static char **str_split_spaces(char *str, size_t *n_words)
{
    char **argv = NULL;
    char *save_ptr;
    char *token;
    int first = 1;
    while (1)
    {
        token = strtok_r(first ? str : NULL, " ", &save_ptr);
        first = 0;
        if (!token)
            break;
        printf("%s\n", token);
        *n_words = *n_words + 1;
        argv = realloc(argv, (*n_words + 1) * sizeof(char*));
        *(argv + *n_words - 1) = strdup(token);
        *(argv + *n_words) = NULL;
    }
    return argv;
}

static char **build_substituted_arg_list(char **args, size_t *n_args, 
        struct hash_table_var *ht)
{
    char **argv = NULL;
    size_t iterator = 0;
    while (*(args + iterator))
    {
        char *substituted = var_substitute(*(args + iterator), ht);
        if (strcmp(substituted, *(args + iterator)))
        {
            //if a substitution did happen, we split the resulting string
            //in space separated words
            size_t n_words = 0;
            char **words = str_split_spaces(substituted, &n_words);
            argv = realloc(argv, (*n_args + n_words + 1) * sizeof(char*));
            for (size_t i = 0; i < n_words; i++)
            {
                *(argv + *n_args + i) = *(words + i);
            }
            *n_args = *n_args + n_words;
            *(argv + *n_args) = NULL;
            free(words);
            free(substituted);
        }
        else
        {
            *n_args = *n_args + 1;
            argv = realloc(argv, (*n_args + 1) * sizeof(char*));
            *(argv + *n_args) = NULL;
            *(argv + *n_args - 1) = substituted;
        }
        iterator++;
    }
    printf("[COMMAND] built arg list: ");
    for (size_t i = 0; i < *n_args; i++)
    {
        printf(" `%s`,", *(argv + i));
    }
    printf("\n");
    return argv;
}

struct command *command_init(char **args, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct command *cmd = calloc(1, sizeof(struct command));
    if (!args || !*args)
    {
        cmd->type = COMMAND_NONE;
        return cmd;
    }
    size_t n_args = 0;
    cmd->args = build_substituted_arg_list(args, &n_args,
            bundle->hash_table_var);
    cmd->n_args = n_args;
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
        free(*(command->args + i));
    }
    free(command->args);
    for (size_t i = 0; i < command->n_redirections; i++)
    {
        redirection_free(*(command->redirections + i));
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

static int command_execute_sh(struct command *command, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!bundle)
        return 0;
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        ////child
        //apply redirection
        //execute command
        execvp(*(command->args), command->args);
        warnx("unknown command: %s", *(command->args));
        //if execution failed
        exit(RETURN_ERROR);
    }
    waitpid(pid, &status, 0);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] command %s received %d\n",
                *(command->args), status);
    }
    return status;
}

static int command_execute_builtin(struct command *command, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    //execute command
    builtin_handler handler = str_to_builtin(*(command->args));
    int execute_handler = handler(command->args, command->n_args,
            bundle_ptr);
    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] builtin %s received %d\n",
                *(command->args), execute_handler);
    }
    return execute_handler;
}

static int command_execute_funcdec(struct command *command, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct ast *func_ast = get_func(bundle->hash_table_func, *(command->args));
    int execute_funcdec = ast_execute(func_ast, bundle_ptr);

    if (bundle->shopt && bundle->shopt->debug)
    {
        printf("[COMMAND EXECUTION] funcdec %s received %d\n",
                *(command->args), execute_funcdec);
    }
    return execute_funcdec;
}

int command_execute(struct command *command, void *bundle_ptr)
{
    int return_value = AST_ERROR;
    command_apply_redirections(command, bundle_ptr);
    if (command->type == COMMAND_AST)
    {
        return_value = ast_execute(command->ast, bundle_ptr);
    }
    if (command->type == COMMAND_SH)
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
    return return_value;
}
