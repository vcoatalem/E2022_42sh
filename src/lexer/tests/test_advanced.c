#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "../lexer.h"

static int token_are_equal(struct token *t1, struct token *t2)
{
    return (t1->type == t2->type && t1->value && t2->value);
}

static int token_array_are_equal(struct token_array *a1, struct token_array *a2)
{
   if (a1->size != a2->size)
   {
        return 0;
   }
   else
   {
        for (size_t i = 0; i < a1->size; i++)
        {
            if (!token_are_equal(*(a1->tok_array + i), *(a2->tok_array + i)))
            {
                return 0;
            }
        }
   }
   return 1;
}

int main(int argc, char **argv)
{
    int q = (argc == 1 ? 0 : atoi(*(argv + 1)));

    char *cmds[] =
    {
        "echo $(subshell)",                         //0
        "echo $(subshell a)",                       //1
        "echo \"$(subshell b)\"",                   //2
        "echo \'$(subshell b)\'",                   //3
        "if $(subshell); then \"$(subshell)\"; fi", //4
        "'echo $(subshell)'",                       //5
        "\"if\"",                                   //6
        "\'if\'",                                   //7
        "\"if\"else",                               //8
        "\'if\'else",                               //9
        "echo \"  d\"",                             //10
        "$(sub\nshell)",                            //11
        "'ec\'ho\'",                                //12
        "if ()",                                    //13
        "$()",                                      //14
        "()",                                       //15
    };
    struct token_array *exp = token_array_init();
    fprintf(stdout, "%s\n", *(cmds + q));
    if (q == 0)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 1)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell a"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 2)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell b"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 3)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "subshell b"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 4)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "$(subshell)"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "$(subshell)"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 5)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo $(subshell)"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 6)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "if"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 7)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "if"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 8)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "ifelse"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 9)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "ifelse"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 10)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "  d"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 11)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "echo $(sub\nshell)"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 12)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 13)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 14)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, ""));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else if (q == 15)
    {
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_EOF, ""));
    }
    else
    {
        return 1;
    }
    struct lexer *lexer = lexer_init();
    lexer_add_string(lexer, cmds[q]);
    struct token_array *array = lex(lexer);
    int eq = token_array_are_equal(array, exp);
    if (!eq)
    {
        fprintf(stderr, "output:\n");
        token_array_print(array, stderr);
        fprintf(stderr, "expected:\n");
        token_array_print(exp, stderr);
        //dump both token arrays
    }
    lexer_free(lexer);
    token_array_free(array);
    token_array_free(exp);
    return eq == 1 ? 0 : 1;
}
