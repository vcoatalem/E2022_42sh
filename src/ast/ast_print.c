#include "ast.h"
#include <stdio.h>
#include <err.h>
#include <errno.h>

char *type_character(enum operator_type type)
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
        if (ast->node_type == NODE_VALUE)
        {
            fprintf(file, "\"%s_%p\";\n\t", ast->content.value, ast_cast);
        }
        else if (ast->node_type == NODE_OPERATOR)
        {
            fprintf(file, "\"%s_%p\";\n\t",
                    type_character(ast->content.op_type), ast_cast);
        }
        else // NODE_EPSILON
        {
            fprintf(file, "\"%s_%p\";\n\t",
                    "EPSILON", ast_cast);
        }
    }

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        if (ast->node_type == NODE_VALUE)
            fprintf(file, "\"%s_%p\"", ast->content.value, ast_cast);

        else
            fprintf(file, "\"%s_%p\"",
                    type_character(ast->content.op_type), ast_cast);

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
