#ifndef PARSER_H
#define PARSER_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"


#define NB_RULES 39
enum rule_id //MORE RULES TO BE ADDED
{
    RULE_NONE,                       //0
    RULE_INPUT,                      //1
    RULE_LIST_DELIM,                 //2
    RULE_LIST_CONCAT,                //3
    RULE_LIST,                       //4
    RULE_COMPOUND_LIST_BREAK_DELIM,  //5
    RULE_COMPOUND_LIST_BREAK_LINE,   //6
    RULE_COMPOUND_LIST_BREAK_CONCAT, //7
    RULE_COMPOUND_LIST_BREAK,        //8
    RULE_COMPOUND_LIST_DELIM,        //9
    RULE_COMPOUND_LIST_CONCAT,       //10
    RULE_COMPOUND_LIST,              //11
    RULE_AND_OR,                     //12
    RULE_AND_OR_CONCAT,              //13
    RULE_AND_CONCAT,                 //14
    RULE_AND_LINEBREAK,              //15
    RULE_OR_CONCAT,                  //16
    RULE_OR_LINEBREAK,               //17
    RULE_PIPELINE,                   //18
    RULE_PIPE,                       //19
    RULE_COMMAND,                    //20
    RULE_SIMPLE_COMMAND,             //21
    RULE_SHELL_COMMAND,              //22
    RULE_REDIR_LIST,                 //23
    RULE_REDIR,                      //24
    RULE_REDIR_SYMBOL,               //25
    RULE_REDIR_TO,                   //26
    RULE_IONUMBER,                   //27
    RULE_ELEMENT,                    //28
    RULE_ELEMENT_LIST,               //29
    RULE_ARG_LIST,                   //30
    RULE_IF,                         //31
    RULE_ELSE_CONCAT,                //32
    RULE_WHILE,                      //33
    RULE_UNTIL,                      //34
    RULE_FOR,                        //35
    RULE_DO_GROUP,                   //36
    RULE_FUNCDEC_BODY,               //37
    RULE_FUNCDEC                     //38
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

//TODO: replace this with actual parse
struct ast *tmp_parse(struct token_array *arr);

struct symbol_array *symbol_array_init(void);
struct symbol_array *symbol_array_dup(struct symbol_array *symbols);
void symbol_array_merge(struct symbol_array *s1, struct symbol_array *s2);
void symbol_array_add(struct symbol_array *symbols, struct symbol *s);
void symbol_array_add_if_not_in(struct symbol_array *symbols, struct symbol *s);
void symbol_array_free(struct symbol_array *arr);
int symbol_array_contains(struct symbol_array *arr, struct symbol *s);
int symbol_array_equal(struct symbol_array *s1, struct symbol_array *s2);

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
void rule_print(struct rule *rule);
void rule_free(struct rule *rule);

//TODO: add more rules
void sh_rule_element_groups            (struct rule_array *rules);
void sh_rule_command_groups            (struct rule_array *rules);
void sh_rule_redir_groups              (struct rule_array *rules);
void sh_rule_pipe_groups               (struct rule_array *rules);
void sh_rule_input                     (struct rule_array *rules);
void sh_rule_and_or_groups             (struct rule_array *rules);
void sh_rule_list_groups               (struct rule_array *rules);
void sh_rule_compound_list_groups      (struct rule_array *rules);
void sh_rule_compound_list_break_groups(struct rule_array *rules);
void sh_rule_do_groups                 (struct rule_array *rules);
void sh_rule_funcdec_groups            (struct rule_array *rules);
void sh_rule_if_groups                 (struct rule_array *rules);

// function initialising all the rules
struct rule_array *rule_array_build(void);

void rule_array_free(struct rule_array *array);
void rule_array_add(struct rule_array *array, struct rule *r);

// ast building functions

enum operator_type rule_id_to_operator(enum rule_id id);
char *rule_id_to_string(enum rule_id id);

// SYMBOL STACK ////////////////////////////////////////////////////////

struct stack_elt
{
    struct symbol *symbol;
    struct stack_elt *next;
    struct ast *ast;
};

struct stack
{
    struct stack_elt *head;
    size_t size;
};

struct stack *stack_init();
void stack_push(struct stack *stack, struct symbol *s, struct ast *parent);
void stack_push_array(struct stack *stack, struct symbol_array *arr,
        struct ast *parent);
struct stack_elt *stack_peak(struct stack *stack);
struct stack_elt *stack_pop(struct stack *stack);
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

int expr_is_epsilon(struct symbol_array *expression);
struct symbol_array *expr_first(struct rule *rule, struct rule_array *rules);
struct symbol_array *rule_first(enum rule_id rule_id, struct rule_array *rules);
struct symbol_array *rule_next(enum rule_id rule_id, struct rule_array *rules,
        int **path_list);
void symbol_array_print(struct symbol_array *s);

// ANALYSIS_TABLE //////////////////////////////////////////////////////

struct analysis_table
{
    struct rule_array *rules;
    size_t n_rules;
    size_t n_symbols;
    struct symbol_array ***transformation_mat;
};

struct analysis_table *table_build(void);
void table_print(struct analysis_table *table);
void table_free(struct analysis_table *table);

// PARSER /////////////////////////////////////////////////////////////

enum parser_state
{
    PARSER_STATE_SUCCESS,
    PARSER_STATE_FAILURE,
    PARSER_STATE_CONTINUE
};

struct parser
{
    enum parser_state state;
    struct stamp *input;
    struct stack *stack;
    struct ast *ast;
};

struct parser *parser_init(struct token_array *tokens);
void parse(struct parser *parser, struct analysis_table *table);
void parser_free(struct parser *parser);

#endif /* PARSER_H */
