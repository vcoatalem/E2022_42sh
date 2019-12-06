#include "lexer/lexer.h"
#include "parser.h"
#include "utils/xalloc.h"

static bool token_is_sop(struct arithmetic_token *token)
{
    return token->type == A_TOKEN_MULTIPLY || token->type == A_TOKEN_DIVIDE;
}

static bool token_is_eop(struct arithmetic_token *token)
{
    return token->type == A_TOKEN_PLUS || token->type == A_TOKEN_MINUS
        || token->type == A_TOKEN_NOT || token->type == A_TOKEN_INVERT
        || token->type == A_TOKEN_BITWISE_AND
        || token->type == A_TOKEN_BITWISE_OR
        || token->type == A_TOKEN_BITWISE_XOR
        || token->type == A_TOKEN_AND
        || token->type == A_TOKEN_OR
        || token->type == A_TOKEN_POWER_N;
    //TODO: some of these types do not belong there
}

static enum arithmetic_ast_type get_expr_type(enum arithmetic_token_type type)
{
    switch (type)
    {
    case A_TOKEN_PLUS:
        return EXPR_ADDITION;
    case A_TOKEN_MINUS:
        return EXPR_SUBTRACTION;
    case A_TOKEN_MULTIPLY:
        return EXPR_MULTIPLICATION;
    case A_TOKEN_DIVIDE:
        return EXPR_DIVISION;
    case A_TOKEN_BITWISE_AND:
        return EXPR_BITWISE_AND;
    case A_TOKEN_BITWISE_OR:
        return EXPR_BITWISE_OR;
    case A_TOKEN_BITWISE_XOR:
        return EXPR_BITWISE_XOR;
    case A_TOKEN_AND:
        return EXPR_AND;
    case A_TOKEN_OR:
        return EXPR_OR;
    case A_TOKEN_NOT:
        return EXPR_NOT;
    case A_TOKEN_INVERT:
        return EXPR_INVERT;
    case A_TOKEN_POWER_N:
        return EXPR_POWER_N;
    default:
        return EXPR_NUMBER;
    }
    return EXPR_NUMBER;
}

/* /!\ forward function declaration /!\
**
** This solves a cyclique dependency between the 3 parsing functions
**
**      exp ----> sexp ----> texp +
**       ^                        |
**       + ---------------------- +
**
** this means at least one function must be declares before the 3 are
** defined.
*/
static bool parse_exp(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast);

static bool parse_parenthesis(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast)
{
    bool res = parse_exp(lexer, ast);

    struct arithmetic_token *token = arithmetic_lexer_pop(lexer);
    res = res && token && token->type == A_TOKEN_RIGHT_PARENTHESIS;

    arithmetic_token_free(token);
    return res;
}

static bool parse_texp(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast)
{
    struct arithmetic_token *token = arithmetic_lexer_pop(lexer);
    if (!token)
        return false;

    bool res = true;
    if (token->type == A_TOKEN_LEFT_PARENTHESIS)
        res = parse_parenthesis(lexer, ast);
    else if (token->type == A_TOKEN_NUMBER)
        *ast  = arithmetic_ast_alloc_number(token->value);
    else if (token->type == A_TOKEN_MINUS)
    {
        arithmetic_token_free(token);
        token = arithmetic_lexer_pop(lexer);

        if (token && token->type == A_TOKEN_NUMBER)
            *ast = arithmetic_ast_alloc_number(-token->value);
        else
            res = false;
    }
    else
        res = false;

    arithmetic_token_free(token);
    return res;
}

static bool parse_sexp(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast)
{
    if (!parse_texp(lexer, ast))
        return false;

    bool res = true;
    struct arithmetic_token *token = arithmetic_lexer_peek(lexer);
    while (res && token && token_is_sop(token))
    {
        token = arithmetic_lexer_pop(lexer);

        struct arithmetic_ast *tmp = arithmetic_ast_alloc();
        
        tmp->type = get_expr_type(token->type);
        if (tmp->type == EXPR_NUMBER)
            res = false;
        res = parse_texp(lexer, &tmp->data.children.right);
        tmp->data.children.left = *ast;
        *ast = tmp;
        arithmetic_token_free(token);
        token = arithmetic_lexer_peek(lexer);
    };

    return res;
}

static bool parse_exp(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast)
{
    if (!parse_sexp(lexer, ast))
        return false;

    bool res = true;
    struct arithmetic_token *token = arithmetic_lexer_peek(lexer);
    while (res && token && token_is_eop(token))
    {
        token = arithmetic_lexer_pop(lexer);

        struct arithmetic_ast *tmp = arithmetic_ast_alloc();
        tmp->type = get_expr_type(token->type);
        if (tmp->type == EXPR_NUMBER)
            res = false;
        res = parse_sexp(lexer, &tmp->data.children.right);
        tmp->data.children.left = *ast;
        *ast = tmp;
        arithmetic_token_free(token);
        token = arithmetic_lexer_peek(lexer);
    };

    return res;
}

bool parse_expression(struct arithmetic_lexer *lexer,
        struct arithmetic_ast **ast)
{
    struct arithmetic_token *token = arithmetic_lexer_peek(lexer);
    if (!token || token->type == A_TOKEN_EOF)
        return false;

    if (!parse_exp(lexer, ast))
        return false;

    token = arithmetic_lexer_pop(lexer);
    bool return_value = token && token->type == A_TOKEN_EOF ? 1 : 0;
    if (token)
    {
        arithmetic_token_free(token);
    }
    return return_value;
}
