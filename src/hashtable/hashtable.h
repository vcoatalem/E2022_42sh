#ifndef HASHTABLE_H
#define HASHTABLE_H


struct HashedVar
{
    //size_t key;
    char *name;
    char *data;
    struct HashedVar *next;
};

struct HashTableVar
{
    size_t size;
    struct HashedVar **items;
};

#endif