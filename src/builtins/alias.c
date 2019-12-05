#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "builtins.h"
#include "../main/42sh.h"

static void print_alias_hash_table_var(struct hash_table_var *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        struct hashed_var *items = ht->items[i];
        while(items)
        {
            if (strcmp(items->data, "") != 0)
                printf("alias %s='%s'\n", items->name, items->data);
            items = items->next;
        }
    }
}


int builtin_alias(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || !str)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        print_alias_hash_table_var(bundle->hash_table_aliases);
        return 0;
    }
    for (size_t i = 1; i < size; ++i)
    {
        int contain_equal = 0;
        for (int j = 0; str[i][j]; ++j)
        {
            if (str[i][j] == '=')
            {
                contain_equal = j;
                break;
            }
        }
        if (!contain_equal)
        {
            char *cmd = get_variable(bundle->hash_table_aliases, str[i]);
            if (!cmd)
            {
                printf("42sh: alias %s not found\n", str[i]);
                return 1;
            }
            printf("alias %s='%s'\n",str[i], cmd);
            free(cmd);
        }
        else
        {
            char *name = strdup(str[i]);
            name[contain_equal] = 0;
            char *value = strdup(str[i]);
            int j = contain_equal;
            for (; value[j]; ++j)
            {
                value[j - contain_equal] = value[j + 1];
            }
            value[j - contain_equal] = 0;
            insert_variable(bundle->hash_table_aliases, name, value);
            free(name);
            free(value);
        }
    }
    return 1;
}


int builtin_unalias(char **str, size_t size, void *bundle_ptr)
{
    if (!bundle_ptr || !str)
        return 1;
    struct execution_bundle *bundle = bundle_ptr;
    if (size == 1)
    {
        return 2;
    }
    if (size == 2 && strcmp(str[1], "-a") == 0)
    {
        free_hash_table_var(bundle->hash_table_aliases);
        bundle->hash_table_aliases = init_hash_table_var(50, 0);
        return 0;
    }
    if (size >= 2)
    {
        for (size_t i = 1; i < size; ++i)
        {
            insert_variable(bundle->hash_table_aliases, str[i], "");
        }
        return 0;
    }
    return 2;

}