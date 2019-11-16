#include "readline.h"

#include <stdio.h>
#include <unistd.h>

#include <readline/readline.h>

static int is_interactive(void)
{
    int tty = rl_instream ? fileno(rl_instream) : fileno(stdin);

    return isatty(tty);
}

static void prep_terminal(int meta_flag)
{
    if (is_interactive())
        rl_prep_terminal(meta_flag);
}

char *get_next_line(const char *prompt)
{
    rl_prep_term_function = prep_terminal;

    if (!is_interactive())
        prompt = NULL;

    return readline(prompt);
}
