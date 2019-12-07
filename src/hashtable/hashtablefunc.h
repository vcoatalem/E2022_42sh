#ifndef HASHTABLEFUNC_H
#define HASHTABLEFUNC_H


struct hashed_func
{
    //size_t key;
    char *name;
    struct ast *ast;
    struct hashed_func *next;
};

struct hash_table_func
{
    size_t size;
    struct hashed_func **items;
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
struct hash_table_func *init_hash_table_func(size_t size);
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
void free_hash_table_func(struct hash_table_func *ht);

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
void insert_func(struct hash_table_func *ht, char *name, struct ast *ast);
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
struct ast *get_func(struct hash_table_func *ht, char *name);

void print_hash_table_func(struct hash_table_func *ht);


#endif /* HASHTABLEFUNC */
