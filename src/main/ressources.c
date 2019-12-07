#include "42sh.h"

static int file_is_readable(char *filename)
{
    int val = 0;
    FILE *f = fopen(filename, "r");
    if (f)
    {
        val = 1;
        fclose(f);
    }
    return val;
}

int load_ressource_files(struct execution_bundle *bundle)
{
    int return_value = 1;
    if (file_is_readable("/etc/42shrc"))
    {
        return_value = execute_script(bundle, "/etc/42shrc");
    }
    char *home_dir = getenv("HOME");
    char filepath[4096] = { 0 };
    strcpy(filepath, home_dir);
    strcat(filepath, "/");
    strcat(filepath, ".42shrc");
    if (file_is_readable(filepath))
    {
        return_value = execute_script(bundle, filepath);
    }
    return return_value;
}
