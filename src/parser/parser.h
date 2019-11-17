#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"


#define NB_RULES 8
enum rule_id //RULES TO BE ADDED
{
    RULE_NONE,
    //RULE_INPUT,
    //RULE_LIST,
    //RULE_AND_OR,
    //RULE_AND,
    //RULE_OR,
    //RULE_PIPELINE,
    RULE_COMMAND,
    //RULE_SIMPLE_COMMAND, 
    RULE_REDIRECTION,
    RULE_REDIRECTION_SYMBOL,
    RULE_REDIRECTION_LIST,
    RULE_IONUMBER,
    RULE_ELEMENT,
    RULE_ARG_LIST,
    //RULE_SHELL_COMMAND,
    //RULE_FUNCDEC,
    //RULE_COMPOUND_LIST,
    //RULE_COMPOUND_LIST_BREAK,
    //RULE_FOR,
    //RULE_WHILE,
    //RULE_CASE,
    //RULE_IF,
    //ELSE_CLAUSE,
    //DO_GROUP,
    //CASE_CLAUSE,
    //CASE_ITEM
};

enum symbol_type
{
    SYMBOL_EPSILON,
    SYMBOL_END,
    SYMBOL_TOKEN,
    SYMBOL_RULE
};

// SYMBOLS ///////////////////////////////////////////////////////////

struct symbol
{
    enum symbol_type type;
    enum token_type token_type;
    enum rule_id rule_id;
};

struct symbol *symbol_epsilon(void);
struct symbol *symbol_end(void);
struct symbol *symbol_create(enum token_type token_type, enum rule_id rule_id);
struct symbol *symbol_dup(struct symbol *s);
void symbol_print(struct symbol *s);

struct symbol_array
{
    struct symbol **array;
    size_t size;
    size_t capacity;
};

struct symbol_array *symbol_array_init(void);
struct symbol_array *symbol_array_dup(struct symbol_array *symbols);
void symbol_array_merge(struct symbol_array *s1, struct symbol_array *s2);
void symbol_array_add(struct symbol_array *symbols, struct symbol *s);
void symbol_array_free(struct symbol_array *arr);

// RULE ///////////////////////////////////////////////////////////////

struct rule //symbol -> array:[symbolA, symbolB, symbolC]
{
    enum rule_id rule_id;
    struct symbol_array *symbols; //array to substitute to src
};

struct rule_array
{
    struct rule **rules;
    size_t size;
    size_t capacity;
};

struct rule *rule_build(enum rule_id id, struct symbol *s, ...);
void rule_free(struct rule *rule);

//TODO: add more rules
void sh_rule_element(struct rule_array *rules);
void sh_rule_arg_list(struct rule_array *rules);
void sh_rule_command(struct rule_array *rules);
void sh_rule_ionumber(struct rule_array *rules);
void sh_rule_redirection(struct rule_array *rules);
void sh_rule_redirection_list(struct rule_array *rules);
void sh_rule_redirection_symbol(struct rule_array *rules);


// function initialising all the rules
struct rule_array *rule_array_build(void);

void rule_array_free(struct rule_array *array);
void rule_array_add(struct rule_array *array, struct rule *r);

// SYMBOL STACK ////////////////////////////////////////////////////////

struct stack_elt
{
    struct symbol *symbol;
    struct stack_elt *next;
};

struct stack
{
    struct stack_elt *head;
    size_t size;
};

struct stack *stack_init();
void stack_push(struct stack *stack, struct symbol *s);
void stack_push_array(struct stack *stack, struct symbol_array *arr);
struct symbol *stack_peak(struct stack *stack);
struct symbol *stack_pop(struct stack *stack);
void stack_print(struct stack *stack);
void stack_free(struct stack *stack);

// STAMP ///////////////////////////////////////////////////////////////

#define STAMP_CONTINUE 0
#define STAMP_STOP 1

struct stamp
{
    struct token_array *tokens;
    size_t pos;
};

struct stamp *stamp_init(struct token_array *tokens);
struct token *stamp_read(struct stamp *stamp);
void stamp_continue(struct stamp *stamp);
void stamp_free(struct stamp *stamp);
int stamp_is_over(struct stamp *stamp);
void stamp_print(struct stamp *stamp);

// EXPRESSION OPERATIONS ///////////////////////////////////////////////

int epsilon(struct symbol_array *expression);
struct symbol_array *first(struct symbol_array *expression,
        struct rule_array *rules);
struct symbol_array *next(enum rule_id rule_id, struct rule_array *rules);
void symbol_array_print(struct symbol_array *s);

// ANALYSIS_TABLE //////////////////////////////////////////////////////

struct analysis_table
{
    size_t n_rules;
    size_t n_symbols;
    struct symbol_array ***transformation_mat;
};

struct analysis_table *table_init(void);
void table_print(struct analysis_table *table);
void table_free(struct analysis_table *table);

// PARSER /////////////////////////////////////////////////////////////

int parse(struct token_array *tokens, struct analysis_table *table);

#endif /* PARSER_H */
