#include <stdlib.h>
#include <stdio.h>

#include "../parser.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    const char *output_file_name = argc <= 1 ? "tmp_more_ast" : *(argv + 2);
    struct token_array *exp = token_array_init();
    enum parser_state expected_parser_state[] =
    {
        PARSER_STATE_SUCCESS,
        PARSER_STATE_FAILURE,
        PARSER_STATE_SUCCESS,
        PARSER_STATE_SUCCESS,
        PARSER_STATE_SUCCESS,
        PARSER_STATE_FAILURE,
        PARSER_STATE_CONTINUE,
        PARSER_STATE_FAILURE
    };
    if (q == 0)
    {
        fprintf(stderr, "simple correct list");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "carpe"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";")); 
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "diem"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 1)
    {
        fprintf(stderr, "uncorrect list");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "aloe"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";")); 
        token_array_add(exp, token_init(TOKEN_AMPERSAND, "&")); 
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "mora"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 2)
    {
        fprintf(stderr, "simple correct list with ending char");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "vale"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "grainde"));
        token_array_add(exp, token_init(TOKEN_AMPERSAND, "&"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 3)
    {
        fprintf(stderr, "simple single-line IF statement");
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_WORD, "B"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 4)
    {
        fprintf(stderr, "simple multi-line IF statement with multiple separators");
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_WORD, "B"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 5)
    {
        fprintf(stderr, "simple multi-line IF statement with multiple separators in wrong order");
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_WORD, "B"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 6)
    {
        fprintf(stderr, "unfinished, correct if command");
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 7)
    {
        fprintf(stderr, "unfinished, doomed if command");
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_ELSE, "else"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else
    {
        return 0;
    }
    struct analysis_table *table = table_build();
    struct parser *p = parser_init(exp);
    parse(p, table);
    ast_dot_print(p->ast, output_file_name);
    int return_value = (p->state == expected_parser_state[q]) ? 0 : 1;
    printf("[LL PARSER] parser state: %d\n", p->state);
    parser_free(p, 1);
    table_free(table);
    return return_value;
}