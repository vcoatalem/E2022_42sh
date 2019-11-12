#include "ast.h"
#include <stdio.h>
#include <err.h>
#include <errno.h>

char *type_character(enum operator_type type)
{
    switch (type)
    {
        case (OPERATOR_CMD):
            return "CMD";

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

void _ast_dot_print(struct ast *ast, int id, FILE *file)
{
    if (ast->node_type == NODE_VALUE)
        fprintf(file, "%s%d", ast->content.value, id);

    else
        fprintf(file, "%s%d", type_character(ast->content.op_type), id);

    if (ast->forest == NULL)
        fprintf(file, "\n");

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        fprintf(file, " --- ");
        _ast_dot_print(ast->forest[i], id + 1, file);
    }
}

void ast_dot_print(struct ast *ast)
{
    FILE *file = fopen("./ast_print.dot", "w");

    if (file == NULL)
        err(errno, "ERROR_AST_PRINT: Cannot open file ast_print.dot");

    _ast_dot_print(ast, 0, file);

    fclose(file);
}
