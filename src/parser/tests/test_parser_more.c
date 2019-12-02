#include <stdlib.h>
#include <stdio.h>

#include "../parser.h"
#include "../../main/42sh.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    const char *output_file_name = argc <= 1 ? "tmp_more_ast" : *(argv + 2);
    struct token_array *exp = token_array_init();
    enum parser_state expected_parser_state[] =
    {
        PARSER_STATE_SUCCESS, //0
        PARSER_STATE_FAILURE, //1
        PARSER_STATE_SUCCESS, //2
        PARSER_STATE_SUCCESS, //3
        PARSER_STATE_SUCCESS, //4
        PARSER_STATE_FAILURE, //5
        PARSER_STATE_CONTINUE,//6
        PARSER_STATE_FAILURE, //7
        PARSER_STATE_SUCCESS, //8
        PARSER_STATE_SUCCESS, //9
        PARSER_STATE_SUCCESS, //10
        PARSER_STATE_SUCCESS, //11
        PARSER_STATE_SUCCESS, //12
        PARSER_STATE_CONTINUE, //13
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
    else if (q == 8)
    {
        fprintf(stderr, "correct funcdec");
        token_array_add(exp, token_init(TOKEN_FUNCTION, "function"));
        token_array_add(exp, token_init(TOKEN_WORD, "function_name"));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_LEFT_BRACKET, "{"));
        token_array_add(exp, token_init(TOKEN_WORD, "line_1"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "line_2"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_RIGHT_BRACKET, "}"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 9)
    {
        fprintf(stderr, "correct while");
        token_array_add(exp, token_init(TOKEN_WHILE, "while"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DO, "do"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DONE, "done"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 10)
    {
        fprintf(stderr, "correct until");
        token_array_add(exp, token_init(TOKEN_UNTIL, "until"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DO, "do"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DONE, "done"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 11)
    {
        fprintf(stderr, "correct until with tricky functions as children");
        token_array_add(exp, token_init(TOKEN_WHILE, "until"));
        token_array_add(exp, token_init(TOKEN_FUNCTION, "function"));
        token_array_add(exp, token_init(TOKEN_WORD, "my_pwd"));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_LEFT_BRACKET, "{"));
        token_array_add(exp, token_init(TOKEN_WORD, "pwd"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_RIGHT_BRACKET, "}"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DO, "do"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DONE, "done"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 12)
    {
        token_array_add(exp, token_init(TOKEN_FOR, "for"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_IN, "in"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "seq 0 1 10"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_DO, "do"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "e"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_DONE, "done"));
    }
    else if (q == 13)
    {
        token_array_add(exp, token_init(TOKEN_WHILE, "while"));
        token_array_add(exp, token_init(TOKEN_FUNCTION, "function"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else
    {
        return 0;
    }
    struct execution_bundle bundle;
    bundle.parser_table = table_build();
    bundle.shopt = shopt_init(NULL);
    bundle.shopt->debug = 1;
    struct parser *p = parser_init(exp, bundle.parser_table);
    parse(p, &bundle);
    ast_dot_print(p->ast, output_file_name);
    int return_value = (p->state == expected_parser_state[q]) ? 0 : 1;
    printf("[LL PARSER] parser state: %d\n", p->state);
    parser_free(p);
    table_free(bundle.parser_table);
    free(bundle.shopt);
    return return_value;
}
