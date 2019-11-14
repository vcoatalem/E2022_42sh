#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

#define PARSE_SUCCESS 0
#define PARSE_FAILURE 1

enum test_type
{
    TEST_NONE, //always succeed
    TEST_PARENT, //try to pass child tests
    TEST_TOKEN, //check if current token is part of the fiven token union
    TEST_RULE //try to execute rule
};

#define NB_RULES 11

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
    RULE_ELEMENT,
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
    int star;
    int plus;
};

// TEST RUNNER STRUCTURE

struct test_runner
{
    struct token_array *token_array;
    size_t pos;
    struct ast *ast;
    //struct test ?
};

struct test *test_init(enum test_type type, struct test_props props,
        int star, int plus);

struct test_runner *test_runner_init(struct token_array *token_array,
        size_t pos);
struct test_runner *test_runner_dup(struct test_runner *tr);
void test_runner_free(struct test_runner *tr);



//RULE STRUCTURE

struct rule
{
    size_t n_recipes;
    struct test **recipes;
};

struct rule *rule_input(void);
struct rule *rule_list(void);
struct rule *rule_and_or(void);
struct rule *rule_and(void);
struct rule *rule_or(void);
struct rule *rule_pipeline(void);
struct rule *rule_command(void);
struct rule *rule_simple_command(void);
struct rule *rule_redirection(void);
struct rule *rule_element(void);

void rule_free(struct rule *rule);

//GRAMMER STRUCTURE

struct grammar
{
    struct rule **rules;
    size_t n_rules;
};

struct grammar *grammar_build(void);

int rule_execute(enum rule_id id, struct test_runner *tr, struct grammar *g);
int test_execute(struct test *r, struct test_runner *tr, struct grammar *g);

struct ast *parse(struct token_array *tokens);

#endif /* PARSER_H */
