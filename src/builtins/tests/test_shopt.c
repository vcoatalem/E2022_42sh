#include <stdio.h>
#include <stdlib.h>

#include "../../main/42sh.h"
#include "../builtins.h"

int main(int argc, char **argv)
{
    int q = argc == 1 ? 0 : atoi(*(argv + 1));
    char *argv1[] =
    {
        "shopt", NULL
    };


    char **args[] =
    {
        argv1,
        NULL
        //...
    };
    int return_value = 0;
    struct options *opt = options_init();
    struct execution_bundle bundle = { 0 };
    bundle.options = opt;
    bundle.shopt = shopt_init(opt);
    if (q == 0)
    {
        //traitements sur loption ici
        return_value = builtin_shopt(args[q], 1, &bundle); 
    }
    /*
    else if (q == 1)
    {

    }
    else if (q == 2)
    {

    }*/
    shopt_free(bundle.shopt);
    options_free(opt);
    return return_value;
}
