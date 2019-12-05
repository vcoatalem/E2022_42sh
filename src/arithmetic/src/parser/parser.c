#include "lexer/lexer.h"
#include "parser.h"
#include "utils/xalloc.h"

static bool token_is_sop(struct arithmetic_token *token)
{
    return token->type == TOKEN_MULTIPLY || token->type == TOKEN_DIVIDE;
}

static bool token_is_eop(struct arithmetic_token *token)
{
    return token->type == TOKEN_PLUS || token->type == TOKEN_MINUS;
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
    res = res && token && token->type == TOKEN_RIGHT_PARENTHESIS;

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
    if (token->type == TOKEN_LEFT_PARENTHESIS)
        res = parse_parenthesis(lexer, ast);
    else if (token->type == TOKEN_NUMBER)
        *ast  = arithmetic_ast_alloc_number(token->value);
    else if (token->type == TOKEN_MINUS)
    {
        arithmetic_token_free(token);
        token = arithmetic_lexer_pop(lexer);

        if (token && token->type == TOKEN_NUMBER)
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
        switch (token->type)
        {
        case TOKEN_MULTIPLY:
            tmp->type = EXPR_MULTIPLICATION;
            break;
        case TOKEN_DIVIDE:
            tmp->type = EXPR_DIVISION;
            break;
        default:
            res = false;
            break;
        }
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
        switch (token->type)
        {
        case TOKEN_PLUS:
            tmp->type = EXPR_ADDITION;
            break;
        case TOKEN_MINUS:
            tmp->type = EXPR_SUBTRACTION;
            break;
        default:
            res = false;
            break;
        }
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
    if (!token || token->type == TOKEN_EOF)
        return false;

    if (!parse_exp(lexer, ast))
        return false;

    token = arithmetic_lexer_pop(lexer);
    bool return_value = token && token->type == TOKEN_EOF ? 1 : 0;
    if (token)
    {
        arithmetic_token_free(token);
    }
    return return_value;
}
