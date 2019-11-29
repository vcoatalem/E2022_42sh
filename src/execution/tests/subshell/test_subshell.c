#include "../../execution.h"

int main()
{
    char *argv[] =
    {
        "exec",
        "./42sh",
        "-c",
        "seq 0 1 10",
        NULL
    };
    char *str = substitute_shell(argv);
    printf("%s\n", str);
    free(str);
    return 0;
}
