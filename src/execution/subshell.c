#include <err.h>

#include "execution.h"
#include "../main/42sh.h"
#include "../hashtable/hashtablevar.h"


static int is_delim(char c, char *ifs)
{
    for (size_t i = 0; ifs[i]; i++)
    {
        if (c == ifs[i])
            return 1;
    }
    return 0;
}

#define FIELD_MAX_SIZE 8192
char **split_fields(char *substituted, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    char *delim = get_variable(bundle->hash_table_var, "IFS");
    //TODO: check proper behaviour to adopt here
    delim = !delim ? " \t\n" : delim;
    char **fields = NULL;
    size_t n_fields = 0;
    char buffer[FIELD_MAX_SIZE] = { 0 };
    size_t buffer_size = 0;
    for (size_t i = 0; substituted[i]; i++)
    {
        if (is_delim(substituted[i], delim) && buffer_size > 0)
        {
            buffer[buffer_size] = 0;
            buffer_size = 0;
            n_fields += 1;
            fields = realloc(fields, (n_fields + 1) * sizeof(char*));
            fields[n_fields - 1] = strdup(buffer);
            fields[n_fields] = NULL;
        }
        else
        {
            buffer[buffer_size] = substituted[i];
            buffer_size++;
        }
    }
    if (buffer_size > 0)
    {
         buffer[buffer_size] = 0;
         buffer_size = 0;
         n_fields += 1;
         fields = realloc(fields, (n_fields + 1) * sizeof(char*));
         fields[n_fields - 1] = strdup(buffer);
         fields[n_fields] = NULL;
    }
    return fields;
}


#define SUBSHELL_MAX_SIZE 8192
//args: { "42sh", "-c", "[subshell content]", NULL }

char *substitute_shell(char *command)
{
    char *bin_name = getenv("SHELL");
    if (!bin_name || strcmp(bin_name, "") == 0)
        return NULL;
    //TODO: replace 42sh by name of executable
    char *args[] =
    {
        bin_name,
        "--norc",
        "-c",
        command,
        NULL
    };
    char *env[] =
    {
        NULL
    };
    int p[2];
    pipe(p);
    pid_t pid = fork();
    int status;
    if (pid == 0)
    {
        dup2(p[PIPE_WRITE], STDOUT_FILENO);
        execve(bin_name, args, env);
        //somthing went wrong..
        warnx("could not initialise subshell...");
        exit (RETURN_UNKNOWN_COMMAND);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    char buffer[SUBSHELL_MAX_SIZE] = { 0 };
    if (status == 0)
        read(p[PIPE_READ], buffer, SUBSHELL_MAX_SIZE - 1);
    return strdup(buffer);
}
