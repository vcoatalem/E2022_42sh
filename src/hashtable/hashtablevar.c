#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "hashtablevar.h"
#include "hashtablefunc.h"


static void insert_default_variables(struct hash_table_var *ht)
{
    insert_variable(ht, "ps1", "42sh$ ");
    insert_variable(ht, "ps2", "> ");
}

struct hash_table_var *init_hash_table_var(size_t size)
{
    struct hash_table_var* ht = malloc(sizeof(struct hash_table_var));
    ht->size = size;
    ht->items = calloc(1, sizeof(struct hashed_var) * size);
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
    if (strcmp(items->name, name) == 0) //We change the data of an existing variable
    {
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
/*
int main()
{
    char *a = "edzeezza";
    char *b = "CHHHHARGGGEEERRR!!";
    struct hash_table_var *HT = init_hash_table(5);
    insert_variable(HT, "lol", "issou");
    insert_variable(HT, "echo", "2");
    insert_variable(HT, "echoa", "2");
    insert_variable(HT, "echo", "42");
    insert_variable(HT, "edho", "42");
    insert_variable(HT, a, b);
    printf("lol :%s\n", get_variable(HT, "edzeezza"));
    print_hash_table(HT);
    free_hash_table(HT);
}
*/