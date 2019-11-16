#include "../parser.h"

int main(int argc, char **argv)
{
    int q = (argc == 1) ? 0 : atoi(*(argv + 1));
    struct grammar *g = grammar_build();
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
    struct ast *ast = parse(exp, g);
    if (!ast)
    {
        grammar_free(g);
        return 1;
    }
    printf("parsed an ast. outputing it to `ast.dot`\n");
    ast_dot_print(ast, "ast.dot");
    grammar_free(g);
    return 0;
}
