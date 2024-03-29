#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include "hashtablevar.h"
#include "hashtablefunc.h"

static char *gethome(void)
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw == NULL)
    {
            return(".");
    }
    return pw->pw_dir;
}

char *getcurrent(void)
{
    char result[2048];
    if (getcwd(result, 2048) == NULL)
        return(".");
    return strdup(result);
}

static void insert_default_variables(struct hash_table_var *ht)
{
    insert_variable(ht, "PS1", "42sh$ ");
    insert_variable(ht, "PS2", "> ");
    insert_variable(ht, "?", "0");
    insert_variable(ht, "OLDPWD", "");
    insert_variable(ht, "HOME", gethome());
    insert_variable(ht, "IFS", " \t\n");
    char histfile[2048] = { 0 };
    strcat(histfile, gethome());
    strcat(histfile, "/");
    strcat(histfile, ".42sh_history");
    insert_variable(ht, "HISTFILE", histfile);
    char el[64];
    sprintf(el, "%d", getuid());
    insert_variable(ht, "UID", el);
}

struct hash_table_var *init_hash_table_var(size_t size, int default_values)
{
    struct hash_table_var *ht = calloc(1, sizeof(struct hash_table_var));
    ht->size = size;
    ht->items = calloc(1, sizeof(struct hashed_var) * size);
    if (default_values)
        insert_default_variables(ht);
    return ht;
}


void free_hash_table_var(struct hash_table_var *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        struct hashed_var *items = ht->items[i];
        while(items)
        {
            struct hashed_var *itemtofree = items;
            free(itemtofree->name);
            free(itemtofree->data);
            //free(itemtofree->next);
            items = items->next;
            free(itemtofree);
        }
        free(items);
    }
    free(ht->items);
    free(ht);
}

void insert_variable(struct hash_table_var *ht, char *name, char *data)
{
    size_t key = hash(name, ht->size);
    struct hashed_var *items = ht->items[key];
    if (!items)
    {
        struct hashed_var *newitem = calloc(1, sizeof(struct hashed_var));
        newitem->name = strdup(name);
        newitem->data = strdup(data);
        newitem->next = NULL;
        ht->items[key] = newitem;
        return;
    }

    while(items->next && strcmp(items->name, name) != 0)
    {
        items = items->next;
    }
    if (strcmp(items->name, name) == 0)
    {
        //We change the data of an existing variable
        free(items->data);
        items->data = strdup(data);
    }
    else
    {
        struct hashed_var *newitem = calloc(1, sizeof(struct hashed_var));
        newitem->name = strdup(name);
        newitem->data = strdup(data);
        newitem->next = NULL;
        items->next = newitem;
    }
}

char *get_variable(struct hash_table_var *ht, char *name)
{
    if (strcmp(name, "RANDOM") == 0)
    {
        time_t t;
        srand((unsigned) time(&t));
        char el[64];
        sprintf(el, "%d", rand() % 32768);
        return strdup(el);
    }
    if (strcmp(name, "$") == 0)
    {
        char el[64];
        sprintf(el, "%d", getpid());
        return strdup(el);
    }

    size_t key = hash(name, ht->size);
    struct hashed_var *items = ht->items[key];
    if (!items)
        return "";
    while(items->next && strcmp(items->name, name) != 0)
    {
        items = items->next;
    }
    if (strcmp(items->name, name) == 0)
    {
        return items->data;
    }
    return "";
}

void print_hash_table_var(struct hash_table_var *ht)
{
    printf("size = %ld\n", ht->size);
    for (size_t i = 0; i < ht->size; ++i)
    {
        printf("i: %ld ", i);
        struct hashed_var *items = ht->items[i];
        while(items)
        {
            printf("name: `%s`, data: `%s` ", items->name, items->data);
            items = items->next;
            if (items)
                printf("## ");
        }
        printf("\n");
    }
}
