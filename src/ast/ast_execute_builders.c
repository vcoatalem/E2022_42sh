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
        if (ast_redir_to->nb_children > 0)
        {
            arg = get_element_value(ast_redir_to->forest[0]);
        }
        else
            arg = get_element_value(ast_redir_to);
    }
    enum symbol_value redir_symbol_value = ast_redir_symbol ?
            get_symbol_value(get_element_value(ast_redir_symbol)) : 0;
    enum symbol_value redir_io_from_value = ast_redir_ionumber ?
            get_symbol_value(get_element_value(ast_redir_ionumber)) : 0;

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
                (n_redirections + 2) * sizeof(void*));
        *(redirections + n_redirections) = NULL;
        *(redirections + n_redirections) = redir;
        ast = ast_list;
    }
    return redirections;
}

char **get_arg_list(struct ast *ast)
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

struct command *get_command(struct ast *ast, void *bundle_ptr)
{
    struct ast *simple_cmd = find_op_type(ast, OPERATOR_COMMAND);

    if (simple_cmd != NULL)
    {
        struct ast *args = find_op_type(simple_cmd, OPERATOR_ARG_LIST);
        //struct ast *redir_list = find_op_type(simple_cmd, OPERATOR_REDIR_LIST);

        char **arg_list = get_arg_list(args);
        // TODO: Add get redirection_list function
        //struct redirection **redirs = get_redirs(redir_list);

        struct command *cmd = command_init(arg_list, bundle_ptr);

        return cmd;
    }

    return NULL;
}
