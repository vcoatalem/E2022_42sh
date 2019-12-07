#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "../lexer.h"

static int token_are_equal(struct token *t1, struct token *t2)
{
    return (t1->type == t2->type && !strcmp(t1->value, t2->value));
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
        "ec\'ho\'",                                 //12
        "if ()",                                    //13
        "$()",                                      //14
        "()",                                       //15
        "allo()",                                   //16
        "\"*.allo\"",                               //17
        "'allo()'",                                 //18
        "'a | b'",                                  //19
        "$(A || B) && 'echo a'",                    //20
        "*",                                        //21
        "\"*\"",                                    //22
        "\'*\'",                                    //23
        "$?",                                       //24
        "\"$?\"",                                   //25
        "\'$?\'",                                   //26
        "`backquoted subshell`;",                   //27
        "for i in ~/",                              //28
        "~",                                        //29
        "\"~\""                                     //30

    };
    if (q > 30)
        return 1;
    struct token_array *exp = token_array_init();
    fprintf(stdout, "%s\n", *(cmds + q));
    if (q == 0)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell"));
    }
    else if (q == 1)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell a"));
    }
    else if (q == 2)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell b"));
    }
    else if (q == 3)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "$(subshell b)"));
    }
    else if (q == 4)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "subshell"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
    }
    else if (q == 5)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "echo $(subshell)"));
    }
    else if (q == 6)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "if"));
    }
    else if (q == 7)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "if"));
    }
    else if (q == 8)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "ifelse"));
    }
    else if (q == 9)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "ifelse"));
    }
    else if (q == 10)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "  d"));
    }
    else if (q == 11)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "sub\nshell"));
    }
    else if (q == 12)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "echo"));
    }
    else if (q == 13)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
    }
    else if (q == 14)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, ""));
    }
    else if (q == 15)
    {
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
    }
    else if (q == 16)
    {
        token_array_add(exp, token_init(TOKEN_FUNCDEC, "allo"));
    }
    else if (q == 17)
    {
        struct token *t = token_init(TOKEN_WORD, "*.allo");
        t->quoted = 1;
        token_array_add(exp, t);
    }
    else if (q == 18)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "allo()"));
    }
    else if (q == 19)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "a | b"));
    }
    else if (q == 20)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "A || B"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_AMPERSAND, "&&"));
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "echo a"));
    }
    else if (q == 21)
    {
        token_array_add(exp, token_init(TOKEN_WORD_EXPAND, "*"));
    }
    else if (q == 22)
    {
        struct token *t = token_init(TOKEN_WORD, "*");
        t->quoted = 1;
        token_array_add(exp, t);
    }
    else if (q == 23)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "*"));
    }
    else if (q == 24)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "$?"));
    }
    else if (q == 25)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "$?"));
    }
    else if (q == 26)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "$?"));
    }
    else if (q == 27)
    {
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "backquoted subshell"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
    }
    else if (q == 28)
    {
        token_array_add(exp, token_init(TOKEN_FOR, "for"));
        token_array_add(exp, token_init(TOKEN_WORD, "i"));
        token_array_add(exp, token_init(TOKEN_IN, "in"));
        token_array_add(exp, token_init(TOKEN_WORD_TILDE, "~/"));
    }
    else if (q == 29)
    {
        token_array_add(exp, token_init(TOKEN_WORD_TILDE, "~"));
    }
    else if (q == 30)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "~"));
    }
    token_array_add(exp, token_init(TOKEN_EOF, ""));
    struct lexer *lexer = lexer_init(NULL);
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
