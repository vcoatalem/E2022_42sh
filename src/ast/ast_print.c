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
    case (OPERATOR_LIST):
        return "list";
    case (OPERATOR_OR):
        return "||";
    case (OPERATOR_PIPE):
        return "|";
    case (OPERATOR_COMMAND):
        return "cmd";
    case (OPERATOR_SHELL_COMMAND):
        return "shell_cmd";
    case (OPERATOR_IF):
        return "if";
    case (OPERATOR_THEN):
        return "then";
    case (OPERATOR_WHILE):
        return "while";
    case (OPERATOR_ELSE):
        return "else";
    case (OPERATOR_ARG_LIST):
        return "args";
    case (OPERATOR_REDIR):
        return "redir";
    case (OPERATOR_REDIR_LIST):
        return "redir_list";
    case (OPERATOR_GET_VALUE):
        return "value";
    case (OPERATOR_FUNC_DECLARATION):
        return "function_declaration";
    case (OPERATOR_GET_IONUMBER):
        return "ionumber";
    case (OPERATOR_GET_REDIR_SYMBOL):
        return "redir_symbol";
    case (OPERATOR_GET_REDIR_TO):
        return "redir_to";
    case (OPERATOR_VAR_DECLARATION):
        return "var_declaration";
    case (OPERATOR_DO):
        return "do";
    // TODO: Add more operator types

    default:
        return "NULL";
    }
}

void _ast_dot_print(struct ast *ast, FILE *file)
{
    if (!ast)
        return;
    void *ast_cast = ast;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        void *child_cast = ast->forest[i];
        fprintf(file, "\"%s(%s)_%p\"",
                ast->value,
                operator_to_string(ast->op_type),
                ast_cast);
        fprintf(file, " -> ");
        fprintf(file, "\"%s(%s)_%p\"\n",
                ast->forest[i]->value,
                operator_to_string(ast->forest[i]->op_type),
                child_cast);
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
