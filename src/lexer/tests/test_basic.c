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
        "echo a || cat b",
        "foo> bar",
        "",
        "echo foo||catbar",
        "if a then b elsedsdfs c",
        "a&&b|c|| d||& e",
        "||",
        "blabla\necho 1>>2",
        "   echo          e        e  foo ||    cat     -e",
        "if pdw && ls; then\n cd;\nelse\n\talias;\nfi",
        "echo ((cat -e))",
        "toto<<-   foo",
        "function func() { echo ok }",
        "aa{bb",
        "toto { foo }",
        "foo{ foo}",
        "echo \"test\"",
        "echo \'test\'",
        "ec\"ho\"",
        "echo \"\'\"",
        "echo '\"'",
        "foo $(toto) $((toto2))",
        "echo to*to*",
        "echo 'to*to'",
        "echo \"to*to\"",
        "&abc()",
        "'echo' A | B&*/*"
    };
    if (q > 26)
        return 1;
    struct token_array *exp = token_array_init();
    fprintf(stdout, "%s\n", *(cmds + q));
    if (q == 0)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "cat"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
    }
    else if (q == 1)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
        token_array_add(exp, token_init(TOKEN_GREAT, ">"));
        token_array_add(exp, token_init(TOKEN_WORD, "bar"));
    }
    else if (q == 2)
    {
    }
    else if (q == 3)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "catbar"));
    }
    else if (q == 4)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_WORD, "elsedsdfs"));
        token_array_add(exp, token_init(TOKEN_WORD, "c"));
    }
    else if (q == 5)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "a"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_AMPERSAND, "&&"));
        token_array_add(exp, token_init(TOKEN_WORD, "b"));
        token_array_add(exp, token_init(TOKEN_PIPE, "|"));
        token_array_add(exp, token_init(TOKEN_WORD, "c"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "d"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_AMPERSAND, "&"));
        token_array_add(exp, token_init(TOKEN_WORD, "e"));
    }
    else if (q == 6)
    {
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
    }
    else if (q == 7)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "blabla"));
        token_array_add(exp, token_init(TOKEN_EOL, "\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_STDIN, "1"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_GREAT, ">>"));
        token_array_add(exp, token_init(TOKEN_STDERR, "2"));
    }
    else if (q == 8)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "e"));
        token_array_add(exp, token_init(TOKEN_WORD, "e"));
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_PIPE, "||"));
        token_array_add(exp, token_init(TOKEN_WORD, "cat"));
        token_array_add(exp, token_init(TOKEN_WORD, "-e"));
    }
    else if (q == 9)
    {
        token_array_add(exp, token_init(TOKEN_IF, "if"));
        token_array_add(exp, token_init(TOKEN_WORD, "pdw"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_AMPERSAND, "&&"));
        token_array_add(exp, token_init(TOKEN_WORD, "ls"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_THEN, "then"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "cd"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_ELSE, "else"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_WORD, "alias"));
        token_array_add(exp, token_init(TOKEN_SEMI_COLON, ";"));
        token_array_add(exp, token_init(TOKEN_EOL, "\\n"));
        token_array_add(exp, token_init(TOKEN_FI, "fi"));
    }
    else if (q == 10)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_LEFT_PARENTHESIS, "("));
        token_array_add(exp, token_init(TOKEN_WORD, "cat"));
        token_array_add(exp, token_init(TOKEN_WORD, "-e"));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
        token_array_add(exp, token_init(TOKEN_RIGHT_PARENTHESIS, ")"));
    }
    else if (q == 11)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "toto"));
        token_array_add(exp, token_init(TOKEN_DOUBLE_LESS_DASH, "<<-"));
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
    }
    else if (q == 12)
    {
        token_array_add(exp, token_init(TOKEN_FUNCTION, "function"));
        token_array_add(exp, token_init(TOKEN_FUNCDEC, "func"));
        token_array_add(exp, token_init(TOKEN_LEFT_BRACKET, "{"));
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "ok"));
        token_array_add(exp, token_init(TOKEN_RIGHT_BRACKET, "}"));
    }
    else if (q == 13)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "aa{bb"));
    }
    else if (q == 14)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "toto"));
        token_array_add(exp, token_init(TOKEN_LEFT_BRACKET, "{"));
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
        token_array_add(exp, token_init(TOKEN_RIGHT_BRACKET, "}"));
    }
    else if (q == 15)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "foo{"));
        token_array_add(exp, token_init(TOKEN_WORD, "foo}"));
    }
    else if (q == 16)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "test"));
    }
    else if (q == 17)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "test"));
    }
    else if (q == 18)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
    }
    else if (q == 19)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "\'"));
    }
    else if (q == 20)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "\""));
    }
    else if (q == 21)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "foo"));
        token_array_add(exp, token_init(TOKEN_SUBSHELL, "toto"));
        token_array_add(exp, token_init(TOKEN_ARITHMETIC, "toto2"));
    }
    else if (q == 22)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD_EXPAND, "to*to*"));
    }
    else if (q == 23)
    { 
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "to*to*"));
    }
    else if (q == 24)
    {
        token_array_add(exp, token_init(TOKEN_WORD, "echo"));
        token_array_add(exp, token_init(TOKEN_WORD, "to*to*"));
    }
    else if (q == 25)
    {
        token_array_add(exp, token_init(TOKEN_AMPERSAND, "&"));
        token_array_add(exp, token_init(TOKEN_FUNCDEC, "abc()"));
    }
    else if (q == 26)
    {
        token_array_add(exp, token_init(TOKEN_WORD_NO_SUBSTITUTION, "echo")); 
        token_array_add(exp, token_init(TOKEN_WORD, "A"));
        token_array_add(exp, token_init(TOKEN_PIPE, "|")); 
        token_array_add(exp, token_init(TOKEN_WORD, "B"));
        token_array_add(exp, token_init(TOKEN_AMPERSAND, "&")); 
        token_array_add(exp, token_init(TOKEN_WORD_EXPAND, "*/*"));
    }
    token_array_add(exp, token_init(TOKEN_EOF, ""));
    struct token_array *array = token_array_create(cmds[q]);
    int eq = token_array_are_equal(array, exp);
    if (!eq)
    {
        fprintf(stderr, "output:\n");
        token_array_print(array, stderr);
        fprintf(stderr, "expected:\n");
        token_array_print(exp, stderr);
        //dump both token arrays
    }
    token_array_free(array);
    token_array_free(exp);
    return eq == 1 ? 0 : 1;
}
