#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"

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

struct symbol
{
    int is_terminal;
    enum token_type token_type;
    enum rule_id rule_id;
};


#define STAMP_CONTINUE 0
#define STAMP_STOP 1

struct stamp
{
    struct token_array *tokens;
    size_t pos;
};

struct stamp *stamp_init(struct token_array *tokens);
struct token *stamp_read(struct stamp *stamp);
int stamp_continue(struct stamp *stamp);
void stamp_free(struct stamp *stamp);

#endif /* PARSER_H */
