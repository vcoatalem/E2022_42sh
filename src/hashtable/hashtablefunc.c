#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../ast/ast.h"
#include "hashtablefunc.h"
#include "hashtablevar.h"

struct hash_table_func *init_hash_table_func(size_t size)
{
    struct hash_table_func *ht = malloc(sizeof(struct hash_table_func));
    ht->size = size;
    ht->items = calloc(1, sizeof(struct hashed_func) * size);
    return ht;
}

void free_hash_table_func(struct hash_table_func *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        struct hashed_func *items = ht->items[i];
        while(items)
        {
            struct hashed_func *itemtofree = items;
            free(itemtofree->name);
            ast_free(itemtofree->ast);
            //free(itemtofree->next);
            items = items->next;
            free(itemtofree);
        }
        free(items);
    }
    free(ht->items);
    free(ht);
}

//add together each char of name by multiplying each char by is index
size_t hash(char *name, size_t ht_size)
{
    size_t result = 0;
    int i = 0;
    for (; name[i]; ++i)
    {
        result += name[i] * i;
    }
    return result % ht_size;
}

void insert_func(struct hash_table_func *ht, char *name, struct ast *ast)
{
    size_t key = hash(name, ht->size);
    struct hashed_func *items = ht->items[key];

    if (!items)
    {
        struct hashed_func *newitem = calloc(1, sizeof(struct hashed_func));
        newitem->name = strdup(name);
        newitem->ast = ast_dup(ast);
        newitem->next = NULL;
        ht->items[key] = newitem;
        return;
    }

    while(items->next && strcmp(items->name, name) != 0)
    {
        items = items->next;
    }
    if (strcmp(items->name, name) == 0) //We change the ast of an existing func
    {
        ast_free(items->ast);
        items->ast = ast_dup(ast);
    }
    else
    {
        struct hashed_func *newitem = calloc(1, sizeof(struct hashed_func));
        newitem->name = strdup(name);
        newitem->ast = ast_dup(ast);
        newitem->next = NULL;
        items->next = newitem;
    }
}

struct ast *get_func(struct hash_table_func *ht, char *name)
{
    size_t key = hash(name, ht->size);
    struct hashed_func *items = ht->items[key];
    if (!items)
        return NULL;
    while(items->next && strcmp(items->name, name) != 0)
    {
        items = items->next;
    }
    if (strcmp(items->name, name) == 0)
    {
        return items->ast;
    }
    return NULL;
}

void print_hash_table_func(struct hash_table_func *ht)
{
    printf("size = %ld\n", ht->size);
    for (size_t i = 0; i < ht->size; ++i)
    {
        printf("i: %ld ", i);
        struct hashed_func *items = ht->items[i];
        while(items)
        {
            printf("name: `%s` ", items->name);
            items = items->next;
            if (items)
                printf("## ");
        }
        printf("\n");
    }
}
