#include <stdlib.h>
#include <stdio.h>

#include "../parser.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    const char *output_file_name = argc <= 1 ? "tmp_ast" : *(argv + 2);
    struct token_array *exp = token_array_init();
    enum parser_state expected_parser_state[] =
    {
        PARSER_STATE_SUCCESS,
        PARSER_STATE_FAILURE,
        PARSER_STATE_SUCCESS,
        PARSER_STATE_SUCCESS,
        PARSER_STATE_SUCCESS
    };
    if (q == 0)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 1)
    {

        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 2)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "Hello"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "World!"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 3)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "Hello"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "World!"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 4)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "\n"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    struct analysis_table *table = table_init();
    struct parser *p = parser_init(exp);
    parse(p, table);
    ast_dot_print(p->ast, output_file_name);
    int return_value = (p->state == expected_parser_state[q]) ? 0 : 1;
    parser_free(p, 1);
    table_free(table);
    return return_value;
}
