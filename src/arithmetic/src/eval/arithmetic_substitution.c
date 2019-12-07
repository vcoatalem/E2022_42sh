#include "ast/ast.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "../../main/42sh.h"

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

static int compute_ast(struct arithmetic_ast *ast, int *error)
{
    if (!ast)
        return 0;
    if (ast->type == EXPR_ADDITION)
    {
        return compute_ast(ast->data.children.left, error)
                + compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_SUBTRACTION)
    {
        return compute_ast(ast->data.children.left, error)
                - compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_MULTIPLICATION)
    {
        return compute_ast(ast->data.children.left, error)
                * compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_DIVISION)
    {
        int right = compute_ast(ast->data.children.right, error);
        if (right == 0)
        {
            *error = 1;
            warnx("arithmetic expression: division by 0");
            return 0;
        }
        return compute_ast(ast->data.children.left, error)
                / right;
    }
    else if (ast->type == EXPR_NOT)
    {
        return compute_ast(ast->data.children.left, error) == 0 ? 1 : 0;
    }
    else if (ast->type == EXPR_INVERT)
    {
        return -(compute_ast(ast->data.children.left, error) + 1);
    }
    else if (ast->type == EXPR_BITWISE_AND)
    {
        return compute_ast(ast->data.children.left, error)
                & compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_BITWISE_OR)
    {
        return compute_ast(ast->data.children.left, error)
                | compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_BITWISE_XOR)
    {
        return compute_ast(ast->data.children.left, error)
                ^ compute_ast(ast->data.children.right, error);
    }
    else if (ast->type == EXPR_AND)
    {
        return (compute_ast(ast->data.children.left, error) != 0
            && compute_ast(ast->data.children.right, error) != 0) ? 1 : 0;
    }
    else if (ast->type == EXPR_OR)
    {
        return (compute_ast(ast->data.children.left, error) != 0
            || compute_ast(ast->data.children.right, error) != 0) ? 1 : 0;
    }
    else if (ast->type == EXPR_POWER_N)
    {

    }
    return ast->data.value;
}

int arithmetic_expression_compute(char *str, int *error, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct arithmetic_lexer *lexer = arithmetic_lexer_alloc(str, bundle_ptr);
    if (bundle->shopt->debug)
    {
        printf("[ARITHMETIC] lexed: ");
        arithmetic_lexer_print(lexer);
    }
    struct arithmetic_ast *ast = NULL;
    int try_parse = parse_expression(lexer, &ast);
    if (try_parse != 0)
    {
        *error = try_parse;
    }
    if (bundle->shopt->debug)
    {
        printf("[ARITHMETIC] ast:");
        print_ast(ast);
        printf("\n");
    }
    arithmetic_lexer_free(lexer);
    int return_value =  ast ? compute_ast(ast, error) : 0;
    arithmetic_ast_free(ast);
    return return_value;
}
