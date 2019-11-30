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
    {EXPR_DIVISION, '/'}
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
        return compute_ast(ast->data.children.left)
                / compute_ast(ast->data.children.right);
    }
    else
    {
        return ast->data.value;
    }
}

#if 0
int main(int argc, char **argv)
{
    if (argc == 1)
        return 0;
    struct lexer *lexer = lexer_alloc(argv[1]);
    struct ast *ast;
    bool try_parse = parse_expression(lexer, &ast);
    if (!try_parse)
    {
        return -1;
    }
    print_ast(ast);
    printf("\n%d\n", compute_ast(ast));
    lexer_free(lexer);
}
#endif
