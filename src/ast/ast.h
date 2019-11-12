#ifndef AST_H
#define AST_H

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
    OPERATION_PIPE,
    //while, until, ..
}

struct ast
{
    enum node_type type;    
    union content
    {
        char *value;
        enum operator_type type;
    };
    struct **ast forest;
    size_t n_children;
};

struct ast *ast_init(enum node_type type, char *value,
        enum operator_type op_type);

void ast_add_child(struct ast *ast, struct ast *children);

struct ast *ast_dup(struct ast *ast);

void ast_free(struct ast *ast);

void ast_dot_print(struct ast *ast);

#endif /* AST_H */
