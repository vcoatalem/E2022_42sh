#include "ast.h"

char *get_element_value(struct ast *ast)
{
    struct ast *element_ast = find_op_type(ast, OPERATOR_GET_VALUE);

    if (element_ast == NULL)
        return NULL;
    return element_ast->forest[0]->value;
}

enum symbol_value
{
    SYMBOL_VAL_LESS = 10,
    SYMBOL_VAL_GREAT = 20,
    SYMBOL_VAL_GREAT_AMPERSAND = 30,
    SYMBOL_VAL_STDIN = 0,
    SYMBOL_VAL_STDOUT = 1,
    SYMBOL_VAL_STDERR = 2
};

static enum symbol_value get_symbol_value(char *str)
{
    if (!strcmp(str, "<"))
        return SYMBOL_VAL_LESS;
    if (!strcmp(str, ">"))
        return SYMBOL_VAL_GREAT;
    if (!strcmp(str, ">&"))
        return SYMBOL_VAL_GREAT_AMPERSAND;
    if (!strcmp(str, "0"))
        return SYMBOL_VAL_STDIN;
    if (!strcmp(str, "1"))
        return SYMBOL_VAL_STDOUT;
    if (!strcmp(str, "2"))
        return SYMBOL_VAL_STDERR;
    return 0;
}

struct redirection *ast_redirection_build(struct ast *ast)
{
    struct ast *ast_redir_to = find_op_type(ast, OPERATOR_GET_REDIR_TO);
    struct ast *ast_redir_symbol = find_op_type(ast,
            OPERATOR_GET_REDIR_SYMBOL);
    struct ast *ast_redir_ionumber = find_op_type(ast,
            OPERATOR_GET_IONUMBER);

    char *arg = NULL;
    if (ast_redir_to)
    {
        if (ast_redir_to->forest[0]->op_type == OPERATOR_GET_IONUMBER)
        {
            //if redir_to is a ionumber
            arg = ast_redir_to->forest[0]->forest[0]->value;
        }
        else
            arg = ast_redir_to->forest[0]->value;
    }
    enum symbol_value redir_symbol_value = ast_redir_symbol ?
            get_symbol_value(ast_redir_symbol->forest[0]->value) : 0;
    enum symbol_value redir_io_from_value = ast_redir_ionumber ?
            get_symbol_value(ast_redir_symbol->forest[0]->value) : 1; 
    //by default, redirection is on STDOUT

    enum REDIRECTION_TYPE type = redir_symbol_value + redir_io_from_value;
    struct redirection *redir = redirection_init(type, arg);
    return redir;
}

struct redirection **ast_redirection_list_build(struct ast *ast)
{
    size_t n_redirections = 0;
    struct redirection **redirections = NULL;
    while (ast)
    {
        struct ast *ast_list = find_op_type(ast, OPERATOR_REDIR_LIST);
        struct ast *ast_redir = find_op_type(ast, OPERATOR_REDIR);
        struct redirection *redir = ast_redirection_build(ast_redir);
        n_redirections++;
        redirections = realloc(redirections,
                (n_redirections + 1) * sizeof(void*));
        *(redirections + n_redirections) = NULL;
        *(redirections + n_redirections - 1) = redir;
        ast = ast_list;
    }
    return redirections;
}

char **ast_arg_list_build(struct ast *ast)
{
    char **arg_list = NULL;
    size_t index = 0;

    while (ast != NULL)
    {
        struct ast *element_list = find_op_type(ast, OPERATOR_ARG_LIST);
        arg_list = realloc(arg_list, (index + 2) * sizeof(char *));
        arg_list[index] = get_element_value(ast);
        arg_list[index + 1] = NULL;
        index++;
        ast = element_list;
    }

    return arg_list;
}

struct command *ast_command_build(struct ast *ast, void *bundle_ptr)
{
    struct ast *simple_cmd = find_op_type(ast, OPERATOR_COMMAND);

    if (simple_cmd != NULL)
    {
        struct ast *args = find_op_type(simple_cmd, OPERATOR_ARG_LIST);
        struct ast *redir_list = find_op_type(simple_cmd, OPERATOR_REDIR_LIST);

        char **arg_list = ast_arg_list_build(args);
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
        }
        //free arglist
        size_t i = 0;
        while (*(arg_list + i))
        {
            free(*(arg_list + i));
            i++;
        }
        free(arg_list);
        //free redirlist
        free(redirs);
        return cmd;
    }

    return NULL;
}
