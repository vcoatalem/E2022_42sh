#ifndef BUILTINS_H
#define BUILTINS_H

#include <stddef.h>

struct shopt           
{                      
    int ast_print;     
    int dotglob;       
    int expand_aliases;
    int extglob;       
    int nocaseglob;    
    int nullglob;      
    int sourcepath;    
    int xpg_echo;      
};

typedef int (*builtin_handler)(char **str, size_t size, void *bundle);

builtin_handler str_to_builtin(char *name);
int builtin_history(char **str, size_t size, void *bundle);

/**
 * \brief Execute the builtin shopt
 *
 * Builtin shopt, display 42sh option , has optional parameter ("-s", "-u", "-q")
 *
 * \param **str array of string 
 * \param size size of **str
 * \param *bundle 
 *
 * \return 0 , 1 if failed
 *
 */
int builtin_shopt(char **str, size_t size, void *bundle);
void shopt_print(struct shopt *shopt, int mode);
struct shopt *shopt_init(void *options_ptr);
void shopt_free(struct shopt *shopt);

#endif/* ( ! BUILTINS_H) */
