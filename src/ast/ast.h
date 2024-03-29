/**
 * \file ast.h
 * \brief file with definition of AST structure and its functions
 * \author alexandre.lyfoung arthur.pannier julien.chau victor.coatalem
 * \version 1.0
 * \date November 19th 2019
 *
 * AST structure used for execution
 *
 */

#ifndef AST_H
#define AST_H

#include <stddef.h>
#include "../execution/execution.h"
#include "../expansion/expansion.h"

#define AST_SUCCESS 0
#define AST_ERROR 1
#define AST_MISSING_ARG 2

struct ast_traversal_context
{
    int loop_depth;
    int found_break;
    int found_continue;
    int found_exit;
};

/**
 * \enum node_type
 * \brief enum contain type of nodes
 *
 * Node types contained in ast
 *
 */
enum node_type
{
    NODE_VALUE,
    NODE_OPERATOR,
};

/**
 * \enum operator_type
 * \brief enum contain operator types
 *
 * Operator types contained in ast
 *
 */
enum operator_type
{
    OPERATOR_NONE,
    OPERATOR_COMMAND,
    OPERATOR_NOT,
    OPERATOR_SHELL_COMMAND,
    OPERATOR_LIST,
    OPERATOR_AND,
    OPERATOR_OR,
    OPERATOR_PIPE,
    OPERATOR_IF,
    OPERATOR_THEN,
    OPERATOR_ELSE,
    OPERATOR_WHILE,
    OPERATOR_FOR,
    OPERATOR_UNTIL,
    OPERATOR_DO,
    OPERATOR_CASE,
    OPERATOR_PATTERN,
    OPERATOR_FUNC_DECLARATION,
    OPERATOR_ARG_LIST,
    OPERATOR_REDIR,
    OPERATOR_REDIR_LIST,
    OPERATOR_GET_VALUE,
    OPERATOR_GET_EXPAND_VALUE,
    OPERATOR_GET_SUBSHELL_VALUE,
    OPERATOR_GET_ARITHMETIC_VALUE,
    OPERATOR_GET_TILDE_VALUE,
    OPERATOR_GET_NO_SUBSTITUTION_VALUE,
    OPERATOR_GET_IONUMBER,
    OPERATOR_GET_REDIR_SYMBOL,
    OPERATOR_GET_REDIR_TO,
    OPERATOR_VAR_DECLARATION
};

/**
 * \struct ast
 * \brief ast structure
 *
 * Contain the type, the value of the node, the number of children and a list of these children
 *
 */
struct ast
{
    enum node_type node_type;
    char *value;
    enum operator_type op_type;
    struct ast **forest;
    size_t nb_children;
};

/**
 * \brief create a ast node
 *
 * Based on type, you only need to define either the value, or the operator type of the node.
 *
 * \param type type of the node
 * \param *value value of the node
 * \param op_type type of the operator of the node
 *
 * \return ast
 */
struct ast *ast_init(char *value, enum operator_type op_type);

/**
 * \brief add a child to the parent ast
 *
 * \param ast parent ast
 * \param children child ast
 *
 */
void ast_add_child(struct ast *ast, struct ast *children);

void ast_remove_child(struct ast *ast, size_t n);

/**
 * \brief duplicate an ast
 *
 * \param ast ast to duplicate
 *
 * \return ast return the duplicated ast
 */
struct ast *ast_dup(struct ast *ast);

/**
 * \brief delete and free the ast from memory
 *
 * \param ast ast to free
 *
 */
void ast_free(struct ast *ast);

/**
 * \brief transform an ast into the dot format and put the result in the output parameter
 *
 * \param ast ast to print
 * \param output output to print on
 *
 */
void ast_dot_print(struct ast *ast, const char *output);

/**
 * \brief remove all epsilon and empty nodes
 *
 * \param ast ast to clean
 *
 */
void ast_clean(struct ast *ast);

/**
 * \brief get the children with the name corresponding to name parameter
 *
 * \param ast parent node
 * \param name name to check
 *
 * \return ast
 */
struct ast *get_child_of_name(struct ast *ast, const char *name);

/**
 * \brief find the children with the corresponding operator type
 *
 * \param ast parent node
 * \param op_type operator type to check
 *
 * \return ast , NULL if not found
 */
struct ast *find_op_type(struct ast *ast, enum operator_type op_type);


/**
 * \brief get the child value from an get_value node
 *
 * \param ast get_value to get child value from
 *
 */
char *get_element_value(struct ast *ast);

/**
 * \brief get all arguments from an arg_list node
 *
 * \param ast arg_list node to get argument from
 *
 */
char **ast_arg_list_build(struct ast *ast, void *bundle_ptr);

/**
 * \brief get all arguments of command type node
 *
 * \param ast ast node to get arguments from
 *
 * \return command return a new command structure
 */
struct command *ast_command_build(struct ast *ast, void *bundle_ptr);


/**
 * \brief get all arguments of redir type node
 *
 * \param ast ast node to get redirection from
 *
 * \return redirection return a new redirection structure
 */
struct redirection *ast_redirection_build(struct ast *ast);


struct redirection **ast_redirection_list_build(struct ast *ast);

/**
 * \brief
 *
 * \param
 *
 */

//char **get_redir_list(struct ast *ast);

// AST EXECUTION

/**
 * \brief typedef for all handlers
 *
 * \param ast ast to get handler from
 *
 * \return *int handler function
 */
typedef int (*operator_handler)(struct ast *ast,
        void *bundle);

/**
 * \brief get the handler corresponding to the operator type
 *
 * \param operator_type operator type to get handler from
 *
 * \return operator_handler resulting handler
 */
operator_handler get_operator_handler(enum operator_type type);

int ast_handle_and_or(struct ast *ast, void *bundle_ptr);
int ast_handle_pipe(struct ast *ast, void *bundle);
int ast_handle_if(struct ast *ast, void *bundle);
int ast_handle_then(struct ast *ast, void *bundle);
int ast_handle_while(struct ast *ast, void *bundle);
int ast_handle_for(struct ast *ast, void *bundle);
int ast_handle_until(struct ast *ast, void *bundle);
int ast_handle_funcdec(struct ast *ast, void *bundle);
int ast_handle_vardec(struct ast *ast, void *bundle_ptr);
int ast_handle_list(struct ast *ast, void *bundle_ptr);
int ast_handle_case(struct ast *ast, void *bundle_ptr);


/**
 * \brief execution function of ast
 *
 * \param ast ast to execute
 *
 * \return int return AST_SUCCESS (= 0) or AST_ERROR (= 1)
 */
int ast_execute(struct ast *ast, void *bundle);

#endif /* AST_H */
