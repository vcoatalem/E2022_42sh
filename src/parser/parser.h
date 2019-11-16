#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

enum test_type
{
    TEST_NONE, //always succeed
    TEST_PARENT, //try to pass child tests
    TEST_TOKEN, //check if current token is part of the fiven token union
    TEST_RULE //try to execute rule
};

#define NB_RULES 15

enum rule_id //RULES TO BE ADDED
{
    RULE_NONE,
    RULE_INPUT,
    RULE_LIST,
    RULE_AND_OR,
    RULE_AND,
    RULE_OR,
    RULE_PIPELINE,
    RULE_COMMAND,
    RULE_SIMPLE_COMMAND, 
    //RULE_SHELL_COMMAND,
    //RULE_FUNCDEC,
    RULE_REDIRECTION,
    RULE_REDIRECTION_SYMBOL,
    RULE_REDIRECTION_LIST,
    RULE_IONUMBER,
    RULE_ELEMENT,
    RULE_ARG_LIST,
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

// TEST STRUCTURE

struct test_props
{
    struct test *sub_test;
    struct token_array *token_union;
    enum rule_id rule_id;
};

struct test
{
    struct test *next;
    enum test_type type;
    struct test_props props;
    int optionnal;
    int repeatable;
};

struct test *test_init(enum test_type type, struct test_props *props,
        int optionnal, int repeatable);
void test_print(struct test *test, FILE *out);
void test_add(struct test *test, struct test *res);
void test_free(struct test *test);

// TEST RUNNER STRUCTURE

enum runner_state
{
    RUNNER_STATE_NONE,
    RUNNER_STATE_SUCCESS,
    RUNNER_STATE_ERROR,
    RUNNER_STATE_NEED_MORE_TOKENS
};

struct test_runner
{
    enum runner_state state;
    struct token_array *token_array;
    size_t pos;
    struct ast *ast;
    //struct test ?
};

struct test_runner *test_runner_init(struct token_array *token_array,
        size_t pos);
struct test_runner *test_runner_dup(struct test_runner *tr);
struct test_runner *test_runner_fork(struct test_runner *tr);
void test_runner_free(struct test_runner *tr);
void test_runner_replace(struct test_runner **tr, struct test_runner *res);

//RULE STRUCTURE

struct rule
{
    size_t n_recipes;
    struct test **recipes;
};

struct rule *rule_init(void);

struct rule *rule_input(void);
struct rule *rule_list(void);
struct rule *rule_and_or(void);
struct rule *rule_and(void);
struct rule *rule_or(void);
struct rule *rule_pipeline(void);
struct rule *rule_command(void);
struct rule *rule_simple_command(void);
struct rule *rule_ionumber(void);
struct rule *rule_redirection_symbol(void);
struct rule *rule_redirection_list(void);
struct rule *rule_redirection(void);
struct rule *rule_element(void);
struct rule *rule_arg_list(void);

void rule_print(struct rule *rule, FILE *out);
void rule_free(struct rule *rule);
void rule_add_test(struct rule *rule, struct test *test);

//GRAMMER STRUCTURE

struct grammar
{
    struct rule **rules;
    size_t n_rules;
};

struct grammar *grammar_build(void);
void grammar_free(struct grammar *grammar);

// grammar building utils
struct test *test_tokens_create(int optionnal, int repeatable,
        enum token_type tok, ...);
struct test *test_rule_create(int optionnal, int repeatable,
        enum rule_id id);
struct test *test_sub_create(int optionnal, int repeatable,
        struct test *t, ...);
//

// parsing functions
void rule_execute(enum rule_id id, struct test_runner *tr, struct grammar *g);
void recipe_execute(struct test *r, struct test_runner *tr, struct grammar *g);

struct ast *parse(struct token_array *tokens, struct grammar *g);

#endif /* PARSER_H */
