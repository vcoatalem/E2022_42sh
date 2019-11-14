#include "../parser.h"

int main(int argc, char **argv)
{
    int q = (argc == 1) ? 0 : atoi(*(argv + 1));
    struct token_array *exp = token_array_init();
    if (q == 0)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "cat"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    struct ast *ast = parse(exp);
    ast_dot_print(ast, "ast.dot");
    return 0;
}
