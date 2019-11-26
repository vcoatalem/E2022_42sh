#ifndef VARIABLES_H
#define VARIABLES_H

#include "../hashtable/hashtablevar.h"

char *var_substitute(char *text, struct hash_table_var *ht);

#endif /* VARIABLES_H */
