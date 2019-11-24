#include <stdlib.h>
#include <stdio.h>

#include "../parser.h"
#include "../../main/42sh.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    const char *output_file_name = argc <= 1 ? "tmp_basic_ast" : *(argv + 2);
    struct token_array *exp = token_array_init();
    enum parser_state expected_parser_state[] =
    {
        PARSER_STATE_SUCCESS,  //0
        PARSER_STATE_CONTINUE, //1
        PARSER_STATE_SUCCESS,  //2
        PARSER_STATE_SUCCESS,  //3
        PARSER_STATE_SUCCESS,  //4
        PARSER_STATE_FAILURE,  //5
        PARSER_STATE_SUCCESS,  //6
        PARSER_STATE_FAILURE,  //7
        PARSER_STATE_SUCCESS,  //8
        PARSER_STATE_SUCCESS,  //9
        PARSER_STATE_SUCCESS,  //10
    };
    if (q == 0)
    {
        fprintf(stderr, "simple command");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 1)
    {
        fprintf(stderr, "unfinished OR");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 2)
    {
        fprintf(stderr, "correct OR");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "Hello"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "World!"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 3)
    {
        fprintf(stderr, "2 simple command lines");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "Hello"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "World!"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 4)
    {
        fprintf(stderr, "simple newline");
        token_array_add(exp, token_init(TOKEN_WORD, "\n"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 5)
    {
        fprintf(stderr, "uncorrect OR");
        token_array_add(exp, token_init(TOKEN_WORD, "this"));
        token_array_add(exp, token_init(TOKEN_WORD, "should"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "fail"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 6)
    {
        fprintf(stderr, "correct pipe with `!`");
        token_array_add(exp, token_init(TOKEN_EXCLAMATION_POINT, "!"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_PIPE, "|"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "B"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 7)
    {
        fprintf(stderr, "uncorrect pipe with 2 `!`");
        token_array_add(exp, token_init(TOKEN_EXCLAMATION_POINT, "!"));
        token_array_add(exp, token_init(TOKEN_EXCLAMATION_POINT, "!"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "fail"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 8)
    {
        fprintf(stderr, "simple redirected command");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "i"));
        token_array_add(exp, token_init(TOKEN_WORD, "love"));
        token_array_add(exp, token_init(TOKEN_WORD, "C"));
        token_array_add(exp, token_init(TOKEN_STDIN, "0"));
        token_array_add(exp, token_init(TOKEN_GREAT, ">"));
        token_array_add(exp, token_init(TOKEN_WORD, "output"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 9)
    {
        fprintf(stderr, "simple redirection of a flux to a filename named '0'");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_STDERR, "2"));
        token_array_add(exp, token_init(TOKEN_GREAT, ">"));
        token_array_add(exp, token_init(TOKEN_STDIN, "0"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 10)
    {
        fprintf(stderr, "simple redirection of a flux to another");
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_STDERR, "2"));
        token_array_add(exp, token_init(TOKEN_GREAT_AMPERSAND, ">&"));
        token_array_add(exp, token_init(TOKEN_STDOUT, "1"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    struct execution_bundle bundle;
    bundle.parser_table = table_build();
    bundle.shopt = shopt_init(NULL);
    bundle.shopt->debug = 1;
    struct parser *p = parser_init(exp);
    parse(p, bundle.parser_table, &bundle);
    ast_dot_print(p->ast, output_file_name);
    int return_value = (p->state == expected_parser_state[q]) ? 0 : 1;
    printf("[LL PARSER] parser state: %d\n", p->state);
    parser_free(p);
    free(bundle.shopt);
    table_free(bundle.parser_table);
    return return_value;
}
