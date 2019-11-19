#ifndef AST_H
#define AST_H

#include <stddef.h>

#define AST_SUCCESS 0
#define AST_ERROR 1


enum node_type
{
    NODE_VALUE,
    NODE_OPERATOR,
    NODE_EPSILON
};

enum operator_type
{
    OPERATOR_NONE,
    OPERATOR_COMMAND,
    OPERATOR_AND,
    OPERATOR_OR,
    OPERATOR_PIPE,
    OPERATOR_IF,
    OPERATOR_IF_BODY,
    OPERATOR_THEN,
    OPERATOR_ELSE,
    OPERATOR_WHILE,
    OPERATOR_FOR,
    OPERATOR_UNTIL,
    OPERATOR_DO,
    OPERATOR_CASE,
    //while, until, ..
};

union content
{
    char *value;
    enum operator_type op_type;
};

struct ast
{
    enum node_type node_type;
    union content content;
    struct ast **forest;
    size_t nb_children;
};

struct ast *ast_init(enum node_type type, char *value,
        enum operator_type op_type);

void ast_add_child(struct ast *ast, struct ast *children);

struct ast *ast_dup(struct ast *ast);

void ast_free(struct ast *ast);

void ast_dot_print(struct ast *ast, const char *output);

void ast_clean(struct ast *ast);

struct ast *get_child_of_name(struct ast *ast, const char *name);

char **get_arg_list(struct ast *ast);

char **get_redir_list(struct ast *ast);

// AST EXECUTION

typedef int (*operator_handler)(struct ast *ast);

operator_handler get_operator_handler(enum operator_type type);

int ast_handle_and(struct ast *ast);
int ast_handle_or(struct ast *ast);
int ast_handle_pipe(struct ast *ast);
int ast_handle_if(struct ast *ast);
int ast_handle_then(struct ast *ast);
int ast_handle_while(struct ast *ast);
int ast_handle_for(struct ast *ast);
int ast_handle_until(struct ast *ast);

int ast_execute(struct ast *ast);
/*
{
    //get handler(ast->type)
    //return execute handler
}
*/


#endif /* AST_H */
