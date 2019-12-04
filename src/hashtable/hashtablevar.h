#ifndef HASHTABLEVAR_H
#define HASHTABLEVAR_H
#include <stddef.h>

struct hashed_var
{
    //size_t key;
    char *name;
    char *data;
    struct hashed_var *next;
};

struct hash_table_var
{
    size_t size;
    struct hashed_var **items;
};

char* getcurrent(void);

/**
 * \brief initialize a HashTable
 *
 * initialize a HashTable
 *
 *
 * \param size_t size of the table
 * \param int default_value init the defaults values
 * \return *token_array token_array of the lexer's string
 */
struct hash_table_var *init_hash_table_var(size_t size, int default_values);
/**
 * \brief free a HashTable
 *
 * free a HashTable
 *
 *
 * \param size_t size the size of the table
 *
 * \return void
 */
void free_hash_table_var(struct hash_table_var *ht);
/**
 * \brief hashing function
 *
 * function that hash the name into a number
 *
 *
 * \param char *name name to be hashed, size_t sizeHT size of the HashTable
 *
 * \return size_t the hashed number
 */
size_t hash(char *name, size_t sizeHT);

/**
 * \brief insert_variable
 *
 * function that insert a variable into the hash table
 *
 *
 * \param struct hash_table_var *ht hash table, char *name name of the variable,
 * char *data data of the variable
 * \return void
 */
void insert_variable(struct hash_table_var *ht, char *name, char *data);
/**
 * \brief get_variable
 *
 * function that return a variable in the hash table
 *
 *
 * \param struct hash_table_var *ht hash table, char *name name of the variable,
 *
 * \return char * the data of the variable
 */
char *get_variable(struct hash_table_var *ht, char *name);

void print_hash_table_var(struct hash_table_var *ht);


#endif
