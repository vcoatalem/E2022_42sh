#include "../execution.h"

#include <stdio.h>

int main()
{
    struct redirection *r1 = redirection_init(STDOUT_TO_ARG, "output");
    redirection_execute(r1);
    printf("this is some text\n");
    redirection_free(r1);
}
