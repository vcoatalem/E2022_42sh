#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>

#include "expansion.h"
#include "fnmatch.h"
#include "string.h"
#include "../main/42sh.h"

struct expansion_args
{
    char *pattern;
    char ***arguments;
    size_t *nb;
    size_t depth;
};

static int case_dotglob(char *file, char *path, char *pattern)
{
    if (strcmp(file, ".") == 0 || strcmp(file, "..") == 0)
        return 1;

    if (fnmatch(pattern, path, 0) == 0)
        return 0;

    return 1;
}

char *to_lowercase(char *s)
{
    char *cpy = calloc(1, strlen(s) * sizeof(char));
    for (size_t i = 0; s[i] != '\0'; i++)
        cpy[i] = tolower(s[i]);

    return cpy;
}

static int case_nocaseglob(char *file, char *path, char *pattern)
{
    if (file[0] == '.' || strcmp(file, "..") == 0)
        return 1;

    char *cpy_path = to_lowercase(path);
    char *cpy_pattern = to_lowercase(pattern);

    if (fnmatch(cpy_pattern, cpy_path, 0) == 0)
    {
        free(cpy_path);
        free(cpy_pattern);
        return 0;
    }

    free(cpy_path);
    free(cpy_pattern);
    return 1;
}

static int case_extglob(char *file, char *path, char *pattern)
{
    if (file[0] == '.' || strcmp(file, "..") == 0)
        return 1;

    if (fnmatch(pattern, path, FNM_EXTMATCH) == 0)
        return 0;

    return 1;
}

static void add_arg(struct expansion_args *args, char *new_path)
{
    *(args->arguments) = realloc(*(args->arguments),
                                (*(args->nb) + 2) * sizeof(char *));
    (*(args->arguments))[*(args->nb)] = strdup(new_path);
    (*(args->arguments))[*(args->nb) + 1] = NULL;
    (*(args->nb))++;
}

static void check_shopt_options(void *bundle_ptr,
                        char *name, char *path, struct expansion_args *args)
{
    struct execution_bundle *bundle = bundle_ptr;

   if ((bundle->shopt->dotglob == 1
           && case_dotglob(name, path, args->pattern) == 0)
       || (bundle->shopt->nocaseglob == 1
           && case_nocaseglob(name, path, args->pattern) == 0)
       || (bundle->shopt->extglob == 1
           && case_extglob(name, path, args->pattern) == 0))
   {
       add_arg(args, path);
   }
}

static void get_find(struct expansion_args *args, char *path, void *bundle_ptr)
{
    if (args->depth == 0)
        return;
    struct dirent *dirent = NULL;
    DIR *dir = opendir(!strcmp(path, "") ? "." : path);

    while ((dirent = readdir(dir)) != NULL)
    {
        char *new_path = calloc(1, strlen(path) + strlen(dirent->d_name) + 2);
        strcat(new_path, path);
        strcat(new_path, dirent->d_name);

        check_shopt_options(bundle_ptr, dirent->d_name, new_path, args);

        if (dirent->d_name[0] ==  '.'
                    || strcmp(dirent->d_name, "..") == 0)
        {
            free(new_path);
            continue;
        }

        else if (fnmatch(args->pattern, new_path, 0) == 0)
        {
            add_arg(args, new_path);
        }

        struct stat st;
        if (stat(new_path, &st) != 0)
        {
            free(new_path);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            new_path = strcat(new_path, "/");
            args->depth--;
            get_find(args, new_path, bundle_ptr);
        }

        free(new_path);
    }
    closedir(dir);
}

char **expand_file_pattern(char *pattern, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    struct expansion_args *args = malloc(sizeof(struct expansion_args));
    char **expanded_args = NULL;
    size_t n_args = 0;
    size_t depth = 1;
    for (size_t i = 0; i < strlen(pattern); i++)
    {
        if (*(pattern + i) == '/')
            depth++;
    }

    args->pattern = pattern;
    args->arguments = &expanded_args;
    args->nb = &n_args;
    args->depth = depth;

    get_find(args, "", bundle_ptr);

    if (bundle->shopt->failglob == 1 && args->nb == 0)
        err(1, "42sh: no match");

    if (bundle->shopt->nullglob == 1 && args->nb == 0)
        pattern = "";

    return *(args->arguments);
}
