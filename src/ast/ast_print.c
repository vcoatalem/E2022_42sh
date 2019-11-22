#include "ast.h"
#include <stdio.h>
#include <err.h>
#include <errno.h>

static char *operator_to_string(enum operator_type type)
{
    switch (type)
    {
        case (OPERATOR_AND):
            return "&&";

        case (OPERATOR_OR):
            return "||";

        case (OPERATOR_PIPE):
            return "|";

        // TODO: Add more operator types

        default:
            return "NULL";
    }
}

void _ast_dot_print(struct ast *ast, FILE *file)
{
    void *ast_cast = ast;
    if (ast->forest == NULL)
    {
        fprintf(file, "\"%s(%s)_%p\";\n\t",
                ast->value,
                operator_to_string(ast->op_type),
                ast_cast);
    }

    for (size_t i = 0; i < ast->nb_children; i++)
    {
            fprintf(file, "\"%s(%s)_%p\"",
                    ast->value,
                    operator_to_string(ast->op_type),
                    ast_cast);

        fprintf(file, " -> ");

        _ast_dot_print(ast->forest[i], file);
    }
}

void ast_dot_print(struct ast *ast, const char *output)
{
    FILE *file = fopen(output, "w");

    if (file == NULL)
        err(errno, "ERROR_AST_PRINT: Could not open %s.", output);

    fprintf(file, "digraph ast {\n\t");
    _ast_dot_print(ast, file);
    fprintf(file, "\r}\n");
    fclose(file);
}
