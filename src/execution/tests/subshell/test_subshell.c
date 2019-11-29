#include "../../execution.h"

int main()
{
    char *str = substitute_shell("seq 0 1 10");
    printf("%s\n", str);
    free(str);
    return 0;
}
