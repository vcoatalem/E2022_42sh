#ifndef AST_H
#define AST_H

#include <stddef.h>

enum node_type
{
    NODE_VALUE,
    NODE_OPERATOR,
};

enum operator_type
{
    OPERATOR_NONE,
    OPERATOR_CMD,
    OPERATOR_AND,
    OPERATOR_OR,
    OPERATOR_PIPE,
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

#endif /* AST_H */
