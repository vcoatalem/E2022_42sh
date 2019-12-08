#define _GNU_SOURCE
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
#include <fnmatch.h>
#include <string.h>
#include <strings.h>

#include "expansion.h"
#include "../main/42sh.h"

struct expansion_args
{
    char *pattern;
    char ***arguments;
    size_t *nb;
};

static int case_dotglob(char *file, char *path, char *pattern)
{
    if (strcmp(file, ".") == 0 || strcmp(file, "..") == 0)
        return 1;

    if (fnmatch(pattern, path, 0) == 0)
        return 0;

    return 1;
}

static int case_nocaseglob(char *file, char *path, char *pattern)
{
    if (file[0] == '.' || strcmp(file, "..") == 0)
        return 1;

    if (fnmatch(pattern, path, FNM_CASEFOLD) == 0)
        return 0;

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

static int check_shopt_options(void *bundle_ptr,
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
       return 0;
   }

   return 1;
}

static void get_find(struct expansion_args *args, char *path,
        size_t depth, void *bundle_ptr)
{
    if (depth == 0)
        return;
    struct dirent *dirent = NULL;
    DIR *dir = opendir(!strcmp(path, "") ? "." : path);

    while ((dirent = readdir(dir)) != NULL)
    {
        char *new_path = calloc(1, strlen(path) + strlen(dirent->d_name) + 2);
        strcat(new_path, path);
        strcat(new_path, dirent->d_name);

        if (check_shopt_options(bundle_ptr, dirent->d_name,
                    new_path, args) == 0)
            add_arg(args, new_path);

        else if (dirent->d_name[0] ==  '.'
                    || strcmp(dirent->d_name, "..") == 0)
        {
            free(new_path);
            continue;
        }

        else if (fnmatch(args->pattern, new_path, 0) == 0)
            add_arg(args, new_path);

        struct stat st;
        if (stat(new_path, &st) != 0)
        {
            free(new_path);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            new_path = strcat(new_path, "/");
            get_find(args, new_path, depth - 1, bundle_ptr);
        }

        free(new_path);
    }
    closedir(dir);
}


static int cmd_expanded_args(char *arg1, char *arg2)
{
    return strcasecmp(arg1, arg2);
}

static void insertion_sort(char **array)
{
    if (!array || !*(array) || !*(array + 1))
        return;
    int n = 1;
    while (*(array + n))
    {
        void *pivot = *(array + n);
        int m = n - 1;
        while (0 <= m && cmd_expanded_args(*(array + m), pivot) > 0)
        {
            *(array + m + 1) = *(array + m);
            m--;
        }
        *(array + m + 1) = pivot;
        n++;
    }
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

    get_find(args, "", depth, bundle_ptr);

    if (bundle->shopt->failglob == 1 && args->nb == 0)
        err(1, "42sh: no match");

    if (bundle->shopt->nullglob == 1 && args->nb == 0)
        pattern = "";
    free(args);
    insertion_sort(expanded_args);
    return expanded_args;
}
