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

/**
 * \brief initialize a HashTable
 *
 * initialize a HashTable
 *
 *
 * \param size_t size of the table
 *
 * \return *token_array token_array of the lexer's string
 */
struct HashTableVar *init_hash_table(size_t size);
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
void free_hash_table(struct HashTableVar *ht);
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
 * \param struct HashTableVar *ht hash table, char *name name of the variable,
 * char *data data of the variable
 * \return void
 */
void insert_variable(struct HashTableVar *ht, char *name, char *data);
/**
 * \brief get_variable
 *
 * function that return a variable in the hash table
 *
 *
 * \param struct HashTableVar *ht hash table, char *name name of the variable,
 *
 * \return char * the data of the variable
 */
char *get_variable(struct HashTableVar *ht, char *name);

void print_hash_table(struct HashTableVar *ht);


#endif