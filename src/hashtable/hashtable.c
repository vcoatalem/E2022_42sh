#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"



struct HashTableVar *initHashTable(size_t size)
{
    struct HashTableVar* ht = malloc(sizeof(struct HashTableVar));
    ht->size = size;
    ht->items = calloc(1, sizeof(struct HashedVar) * size);
    return ht;

}


size_t hash(char *name, size_t sizeHT) //add together each char of name by multiplying each char by is index
{
    size_t result = 0;
    int i = 0;
    for (; name[i]; ++i)
    {
        result += name[i] * i;
    }
    return result % sizeHT;
}
/*
size_t hash(char *name, size_t sizeHT) //add each ascii char of name together * the size of the the name
{
    size_t result = 0;
    int i = 0;
    for (; name[i]; ++i)
    {
        result += name[i];
    }
    result *= i;
    return result % sizeHT;
}*/

void insertVariable(struct HashTableVar *ht, char *name, char *data)
{
    size_t key = hash(name, ht->size);
    struct HashedVar *items = ht->items[key];

    if (!items)
    {
        struct HashedVar *newitem = calloc(1, sizeof(struct HashedVar));
        newitem->name = name;
        newitem->data = data;
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
        items->data = data;
    }
    else
    {
        struct HashedVar *newitem = calloc(1, sizeof(struct HashedVar));
        newitem->name = name;
        newitem->data = data;
        newitem->next = NULL;
        items->next = newitem;
    }
}

char *getVariable(struct HashTableVar *ht, char *name)
{
    size_t key = hash(name, ht->size);
    struct HashedVar *items = ht->items[key];
    if (!items)
        return "";
    while(items->next && strcmp(items->name, name) != 0)
    {
        items = items->next;
    }
    if (strcmp(items->name, name) == 0) //We change the data of an existing variable
    {
        return items->data;
    }
    return "";



}

void printHashTable(struct HashTableVar *ht)
{
    printf("size = %ld\n", ht->size);
    for (size_t i = 0; i < ht->size; ++i)
    {
        printf("i: %ld ", i);
        struct HashedVar *items = ht->items[i];
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

int main()
{
    struct HashTableVar *HT = initHashTable(5);
    insertVariable(HT, "lol", "issou");
    insertVariable(HT, "echo", "2");
    insertVariable(HT, "echoa", "2");
    insertVariable(HT, "echo", "42");
    insertVariable(HT, "edho", "42");
    insertVariable(HT, "edzeezz", "42");
    printf("lol :%s\n", getVariable(HT, "edzeezza"));
    printHashTable(HT);
}

