#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "expansion.h"
#include "fnmatch.h"
#include "string.h"

void get_find(const char *pattern, char *path,
                            char ***arguments, size_t *nb)
{
    struct dirent *dirent = NULL;
    DIR *dir = opendir(path);

    while ((dirent = readdir(dir)) != NULL)
    {
        char *new_path = calloc(1, strlen(path) + strlen(dirent->d_name) + 2);
        strcat(new_path, path);
        strcat(new_path, dirent->d_name);
        //printf("%zu: %s\n", *nb, new_path);

        struct stat st;
        if (strcmp(dirent->d_name, ".") == 0
                || strcmp(dirent->d_name, "..") == 0)
        {
            free(new_path);
            continue;
        }

        if (stat(new_path, &st) != 0)
        {
            free(new_path);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            new_path = strcat(new_path, "/");
            get_find(pattern, new_path, arguments, nb);
        }
        
        if (fnmatch(pattern, new_path, 0) == 0)
        {
            *arguments = realloc(*arguments, (*nb + 2) * sizeof(char *));
            (*arguments)[*nb] = strdup(new_path);
            (*arguments)[*nb + 1] = NULL;
            (*nb)++;
        }
        free(new_path);
    }
    closedir(dir);
}
