/**
 * \file parser.h
 * \brief file with definition of PARSER structure and its functions
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 19th 2019
 *
 * LL PARSER grammar structures
 * first(), next() operations
 * analysis table building
 * parser stack initialisation and manipulation
 * derivation ast creation
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"


#define NB_RULES 41


/**
 * \enum rule_id
 * \brief enum contains id of all grammar rule we wish to differenciate
 *
 */
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
    RULE_THEN,                       //32
    RULE_ELSE_CONCAT,                //33
    RULE_WHILE,                      //34
    RULE_UNTIL,                      //35
    RULE_FOR,                        //36
    RULE_DO_GROUP,                   //37
    RULE_FUNCDEC_BODY,               //38
    RULE_FUNCDEC,                    //39
    RULE_VARDEC                      //40
};

/**
 * \enum symbol_type
 * \brief enum contains all symbol types we wish to differenciate
 *
 */
enum symbol_type
{
    SYMBOL_EPSILON,
    SYMBOL_END,
    SYMBOL_TOKEN,
    SYMBOL_RULE
};

// SYMBOLS ///////////////////////////////////////////////////////////

/**
 * \struct symbol
 * \brief data representation of a symbol within a rule
 *
 * Contains the type, a token_type and a rule_id, only one of which will be
 * considered according to the type - similar to how a union would work,
 * but more flexible and easier to manipulate
 *
 */
struct symbol
{
    enum symbol_type type;
    enum token_type token_type;
    enum rule_id rule_id;
};


/**
 * \brief creates a symbol with epsilon type
 */
struct symbol *symbol_epsilon(void);


/**
 * \brief creates a symbol with end type
 */
struct symbol *symbol_end(void);


/**
 * \brief creates a symbol
 *
 * \param token_type token_type of the symbol
 * \param rule_id rule_id of the node
 *
 */
struct symbol *symbol_create(enum token_type token_type, enum rule_id rule_id);


/**
 * \brief allocate and copy symbol
 *
 * \param symbol to be dupplicated
 *
 */
struct symbol *symbol_dup(struct symbol *s);

void symbol_print(struct symbol *s);


/**
 * \struct symbol_array
 * \brief contains multiple symbols
 *
 * Can be used to represent a rule expression or a list of symbols alike
 *
 */
struct symbol_array
{
    struct symbol **array;
    size_t size;
    size_t capacity;
};


/**
 * \brief allocates an empty symbol_array
 *
 */
struct symbol_array *symbol_array_init(void);


/**
 * \brief allocates and copy a symbol_array
 *
 * \param symbol_array to be dupplicated
 */
struct symbol_array *symbol_array_dup(struct symbol_array *symbols);

/**
 * \brief merge 2 symbol arrays into the same one
 *
 * add any element of s2 that is not in s1 to s1, then proceed to free s2
 *
 * \param symbol_array s1 symbol_array to merge into
 * \param symbol_array s2 symbol_array to merge from
 */
void symbol_array_merge(struct symbol_array *s1, struct symbol_array *s2);

/**
 * \brief add a symbol to a symbol_array
 *
 * \param symbol_array symbol_array to add a symbol in
 * \param symbol symbol to add in the array
 */
void symbol_array_add(struct symbol_array *symbols, struct symbol *s);

/**
 * \brief add a symbol to a symbol_array if it is not in the array
 *
 * \param symbol_array symbol_array to add a symbol in
 * \param symbol symbol to add in the array
 */
void symbol_array_add_if_not_in(struct symbol_array *symbols, struct symbol *s);

void symbol_array_free(struct symbol_array *arr);
int symbol_array_contains(struct symbol_array *arr, struct symbol *s);
int symbol_array_equal(struct symbol_array *s1, struct symbol_array *s2);

// RULE ///////////////////////////////////////////////////////////////

/**
 * \struct rule
 * \brief contains multiple symbol_array that represents 'recipes' for
 * \brief this rule
 *
 */
struct rule
{
    enum rule_id rule_id;
    struct symbol_array *symbols;
};

/**
 * \struct rule_array
 * \brief contains multiple rules
 *
 * representation of our LL grammar
 */
struct rule_array
{
    struct rule **rules;
    size_t size;
    size_t capacity;
};

/**
 * \brief create a rule recipe
 *
 * \param rule_id id of the rule we are creating a recipe for
 *
 * build a new rule using all the symbols passed in the NULL terminated
 * va_list of symbols
 */
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
void sh_rule_misc                      (struct rule_array *rules);

/**
 * \brief initialises the LL grammar
 *
 */
struct rule_array *rule_array_build(void);

void rule_array_free(struct rule_array *array);
void rule_array_add(struct rule_array *array, struct rule *r);

// ast building functions

enum operator_type rule_id_to_operator(enum rule_id id);
char *rule_id_to_string(enum rule_id id);

// SYMBOL STACK ////////////////////////////////////////////////////////

/**
 * \struct stack_elt
 * \brief contains a symbol and the ast to push subsequent stack_elt ast to
 *
 */
struct stack_elt
{
    struct symbol *symbol;
    struct stack_elt *next;
    struct ast *ast;
};

/**
 * \struct stack
 * \brief LL parser stack
 *
 * symbols pop'ed cause other symbols to be pushed onto the stack and ast to
 * appended to the ast of the last pop'ed stack_elt
 *
 */
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
void stack_elt_free(struct stack_elt *elt);
void stack_free(struct stack *stack);

// STAMP ///////////////////////////////////////////////////////////////

#define STAMP_CONTINUE 0
#define STAMP_STOP 1


/**
 * \struct stamp
 * \brief token_array reader
 *
 * reads through token_array
 */
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

/**
 * \brief returns a list of symbols that are susceptible of starting
 * \brief the expression contained by rule
 */
struct symbol_array *expr_first(struct rule *rule, struct rule_array *rules);

/**
 * \brief returns a list of symbols that are susceptible of starting
 * \brief any recipe for rule_id
 */
struct symbol_array *rule_first(enum rule_id rule_id, struct rule_array *rules);

/**
 * \brief Returns a list of symbols that are susceptible of following
 * \brief any recipe for rule_id
 */
struct symbol_array *rule_next(enum rule_id rule_id, struct rule_array *rules,
        int **path_list);
void symbol_array_print(struct symbol_array *s);

// ANALYSIS_TABLE //////////////////////////////////////////////////////

/**
 * \struct analysis_table
 * \brief LL parser analysis table
 *
 * Contains a matrix for association rule_id/token which gives the expression
 * to push onto the parser stack when popping a symbol of rule_id for any
 * stamp current token
 *
 */
struct analysis_table
{
    struct rule_array *rules;
    size_t n_rules;
    size_t n_symbols;
    struct symbol_array ***transformation_mat;
};

/**
 * \brief Initialised grammar through rule_array_build(), then
 * \brief initialised analysis table associated with the LL grammar built
 */
struct analysis_table *table_build(void);
void table_print(struct analysis_table *table);
void table_free(struct analysis_table *table);

// PARSER /////////////////////////////////////////////////////////////

/**
 * \enum parser_state
 * \brief enum contains all parser_state we wish to differenciate
 * PARSER_STATE_SUCCESS means parser recognised a rule
 * PARSER_STATE_ERROR means parser recognised the token array it was provided
 * with can not ever be recognised as a rule
 * PARSER_STATE_CONTINUE means parser recognised the token array it was provided * may eventually represent a rule if given more tokens
 */
enum parser_state
{
    PARSER_STATE_SUCCESS,
    PARSER_STATE_FAILURE,
    PARSER_STATE_CONTINUE
};

/**
 * \struct parser
 * \brief LL parser
 *
 * Contains a state to communicate parse() result, a stamp to read on a
 * token_array, a stack to process rules as well as an ast to append
 * the first stack node to.
 */
struct parser
{
    enum parser_state state;
    struct stamp *input;
    struct stack *stack;
    struct ast *ast;
};

/**
 * \brief initialises a root ast, a stack whose first element points toward
 * \brief that ast as well a stamp on the token_array provided
 */
struct parser *parser_init(struct token_array *tokens);

/**
 * \brief run parser procedure and set state accordingly
 */
void parse(struct parser *parser, struct analysis_table *table);
void parser_free(struct parser *parser);

int token_type_is_value(enum token_type type);

#endif /* PARSER_H */
