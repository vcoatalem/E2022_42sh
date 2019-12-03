#ifndef BUILTINS_H
#define BUILTINS_H

#include <stddef.h>

struct shopt           
{
    int debug;
    int ast_print;     
    int dotglob;       
    int expand_aliases;
    int extglob;
    int failglob;
    int nocaseglob;    
    int nullglob;      
    int sourcepath;    
    int xpg_echo;      
};
char *shopt_SHELLOPTS(struct shopt *shopt);

typedef int (*builtin_handler)(char **argv, size_t size, void *bundle_ptr);

builtin_handler str_to_builtin(char *name);
int builtin_alias(char **str, size_t size, void *bundle_ptr);

int builtin_cd(char **argv, size_t size, void *bundle_ptr);

int builtin_export(char **argv, size_t size, void *bundle_ptr);

int builtin_history(char **argv, size_t size, void *bundle_ptr);

int builtin_break(char **argv, size_t size, void *bundle_ptr);

int builtin_continue(char **argv, size_t size, void *bundle_ptr);

int builtin_exit(char **argv, size_t size, void *bundle_ptr);

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
int builtin_shopt(char **argv, size_t size, void *bundle_ptr);
void shopt_print(struct shopt *shopt, int mode);
struct shopt *shopt_init(void *options_ptr);
void shopt_free(struct shopt *shopt);

#endif/* ( ! BUILTINS_H) */
