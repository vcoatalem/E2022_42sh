#include "../ast.h"

enum symbol_value
{
    SYMBOL_VAL_LESS = 10,
    SYMBOL_VAL_GREAT = 20,
    SYMBOL_VAL_GREAT_AMPERSAND = 30,
    SYMBOL_VAL_DOUBLE_GREAT = 40,
    SYMBOL_VAL_DOUBLE_LESS = 50,
    SYMBOL_VAL_DOUBLE_LESS_DASH = 60,
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
    if (!strcmp(str, ">>"))
        return SYMBOL_VAL_DOUBLE_GREAT;
    if (!strcmp(str, "<<"))
        return SYMBOL_VAL_DOUBLE_LESS;
    if (!strcmp(str, "<<-"))
        return SYMBOL_VAL_DOUBLE_LESS_DASH;
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
            get_symbol_value(ast_redir_ionumber->forest[0]->value) : 1;
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
