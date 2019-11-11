#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include "readline.h"
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *input = NULL;

    while (1)
    {
        input = get_next_line("21sh$ ");

        if (!input)
            break;

        printf("%s\n", input);
        free(input);
    }

    return 0;
}
