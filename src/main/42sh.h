#ifndef BASH_H
#define BASH_H

enum BASH_RETURN_VALUES
{
    BASH_RETURN_OK = 0,
    BASH_RETURN_ERROR = 1,
    BASH_RETURN_OPTIONS_ERROR = 2
};

struct execution_bundle
{
    struct options *options;
    struct grammar *grammar;
};

void appendhistory(char *cmd);

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "execute.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../options/options.h"



#endif /* BASH_H */
