#include "expansion.h"
#include "../main/42sh.h"

char *tilde_substitute(char *str, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (!strcmp(str, "~"))
    {
        return strdup(get_variable(bundle->hash_table_var, "HOME"));
    }
    else if (!strcmp(str, "~-"))
    {
        return strdup(get_variable(bundle->hash_table_var, "OLDPWD"));
    }
    else if (!strcmp(str, "~+"))
    {
        return strdup(get_variable(bundle->hash_table_var, "PWD"));
    }
    return strdup(str);
}
