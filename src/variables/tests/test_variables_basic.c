#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../variables.h"

static int test_comparison(char *s1, char *s2)
{
    fprintf(stdout, "%s", s1);
    if (!strcmp(s1, s2))
        return 0;
    fprintf(stderr, "`%s` != `%s`", s1, s2);
    return 1;
}

int main(int argc, char **argv)
{
    size_t q = argc == 1 ? 0 : atoi(*(argv + 1));
    struct hash_table_var *ht = init_hash_table_var(10);
    insert_variable(ht, "var1", "easy");
    insert_variable(ht, "var2", "harder");
    insert_variable(ht, "v", "");
    insert_variable(ht, "var3", "this");
    insert_variable(ht, "var4", "var4");
    insert_variable(ht, "w", "what did you expect");
    insert_variable(ht, "var5", "$var3 is $var1");
  

    char *strings[] =
    {
        "this should be $var1",
        "$v",
        "$w",
        "$var3 $v sho$v uld be $harder",
        "adjacent variables: $v$var1",
        "recursive variables: $var5"
    };
    char *expected[] =
    {
        "this should be easy",
        "",
        "what did you expect",
        "this  sho uld be ",
        "adjacent variables: easy",
        "recursive variables: this is easy"
    };

    if (q >= sizeof(strings) / sizeof(void*))
        return 0;

    int r = test_comparison(var_substitute(strings[q], ht), expected[q]);
    free_hash_table_var(ht);
    return r;
}
