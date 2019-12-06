#include "ast/ast.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

#include <err.h>
#include <stdio.h>

static struct
{
    enum arithmetic_ast_type type;
    char c;
}

ast_char[EXPR_NUMBER] =
{
    {EXPR_ADDITION, '+'},
    {EXPR_SUBTRACTION, '-'},
    {EXPR_MULTIPLICATION, '*'},
    {EXPR_DIVISION, '/'},
    {EXPR_BITWISE_OR, '|'},
    {EXPR_BITWISE_AND, '&'},
    {EXPR_BITWISE_XOR, '^'},
    {EXPR_AND, 'A'},
    {EXPR_OR, 'O'},
    {EXPR_POWER_N, 'P'},
    {EXPR_NOT, '!'},
    {EXPR_INVERT, '~'},
};

void print_ast(struct arithmetic_ast *ast)
{
    if (!ast)
        return;

    if (ast->type == EXPR_NUMBER)
    {
        printf("%d", ast->data.value);
        return;
    }

    printf("(");
    print_ast(ast->data.children.left);
    for (size_t i = 0; i < sizeof(ast_char) / sizeof(*ast_char); ++i)
    {
        if (ast_char[i].type == ast->type)
        {
            printf("%c", ast_char[i].c);
            break;
        }
    }
    print_ast(ast->data.children.right);
    printf(")");
}

int compute_ast(struct arithmetic_ast *ast)
{
    if (!ast)
        return 0;
    if (ast->type == EXPR_ADDITION)
    {
        return compute_ast(ast->data.children.left)
                + compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_SUBTRACTION)
    {
        return compute_ast(ast->data.children.left)
                - compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_MULTIPLICATION)
    {
        return compute_ast(ast->data.children.left)
                * compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_DIVISION)
    {
        int right = compute_ast(ast->data.children.right);
        if (right == 0)
        {
            warnx("arithmetic expression: division by 0");
            return 0;
        }
        return compute_ast(ast->data.children.left)
                / right;
    }
    else if (ast->type == EXPR_NOT)
    {
        return compute_ast(ast->data.children.left) == 0 ? 1 : 0;
    }
    else if (ast->type == EXPR_INVERT)
    {
        return -(compute_ast(ast->data.children.left) + 1);
    }
    else if (ast->type == EXPR_BITWISE_AND)
    {
        return compute_ast(ast->data.children.left)
                & compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_BITWISE_OR)
    {
        return compute_ast(ast->data.children.left)
                | compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_BITWISE_XOR)
    {
        return compute_ast(ast->data.children.left)
                ^ compute_ast(ast->data.children.right);
    }
    else if (ast->type == EXPR_AND)
    {
        return (compute_ast(ast->data.children.left) != 0
            && compute_ast(ast->data.children.right) != 0) ? 1 : 0;
    }
    else if (ast->type == EXPR_OR)
    {
        return (compute_ast(ast->data.children.left) != 0
            || compute_ast(ast->data.children.right) != 0) ? 1 : 0;
    }
    else if (ast->type == EXPR_POWER_N)
    {

    }
    return ast->data.value;
}

int arithmetic_expression_compute(char *str, void *bundle_ptr)
{
    struct arithmetic_lexer *lexer = arithmetic_lexer_alloc(str, bundle_ptr);
    //arithmetic_lexer_print(lexer);
    struct arithmetic_ast *ast = NULL;
    parse_expression(lexer, &ast);
    //print_ast(ast);
    //printf("\n");
    arithmetic_lexer_free(lexer);
    int return_value =  ast ? compute_ast(ast) : 0;
    arithmetic_ast_free(ast);
    return return_value;
}
