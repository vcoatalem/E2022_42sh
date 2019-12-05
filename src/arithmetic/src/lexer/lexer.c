#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

#include "lexer.h"
#include "token_list.h"

struct arithmetic_token *arithmetic_token_init(
        enum arithmetic_token_type type, int value)
{
    struct arithmetic_token *res = malloc(sizeof(struct arithmetic_token));
    if (!res)
        return NULL;
    res->type = type;
    res->value = value;
    return res;
}

struct arithmetic_token_list *arithmetic_token_list_init(
        struct arithmetic_token *token)
{
    struct arithmetic_token_list *tok_list = malloc(
            sizeof(struct arithmetic_token_list));
    if (!tok_list)
    {
        return NULL;
    }
    tok_list->token = token;
    tok_list->next = NULL;
    return tok_list;
}

enum arithmetic_token_type get_type(char c)
{
    enum arithmetic_token_type type;
    switch (c)
    {
    case '+':
        type = TOKEN_PLUS;
        break;
    case '-':
        type = TOKEN_MINUS;
        break;
    case '*':
        type = TOKEN_MULTIPLY;
        break;
    case '/':
        type = TOKEN_DIVIDE;
        break;
    case '(':
        type = TOKEN_LEFT_PARENTHESIS;
        break;
    case ')':
        type = TOKEN_RIGHT_PARENTHESIS;
        break;
    case EOF:
        type = TOKEN_EOF;
        break;
    default:
        type = TOKEN_NUMBER;
        break;
    }
    return type;
}

void arithmetic_token_list_append(struct arithmetic_lexer *lexer,
        struct arithmetic_token *tok)
{
    struct arithmetic_token_list *res = arithmetic_token_list_init(tok);
    if (lexer->size == 0)
    {
        lexer->head = res;
        lexer->tail = res;
    }
    else
    {
        lexer->tail->next = res;
        lexer->tail = res;
    }
    lexer->size++;
}

void add_number_token(char *buff, size_t *index,
        struct arithmetic_lexer *lexer)
{
    if (*index == 0)
        return;
    buff[*index] = '\0';
    int val = atoi(buff);
    *index = 0;
    struct arithmetic_token *tok = arithmetic_token_init(TOKEN_NUMBER, val);
    arithmetic_token_list_append(lexer, tok);
}

struct arithmetic_lexer *arithmetic_lexer_alloc(const char *str)
{
    struct arithmetic_lexer *res = calloc(1, sizeof(struct arithmetic_lexer));
    if (!res)
    {
        return NULL;
    }
    // transform *str to a char token
    char buff[1024] = { 0 };
    size_t index = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        enum arithmetic_token_type type = get_type(c);
        if (type != TOKEN_NUMBER || c == ' ')
        {
            add_number_token(buff, &index, res);
            if (c != ' ')
            {
                struct arithmetic_token *tok = arithmetic_token_init(type, 0);
                arithmetic_token_list_append(res, tok);
            }
        }
        else
        {
            buff[index] = c;
            index++;
        }
    }
    add_number_token(buff, &index, res);
    arithmetic_token_list_append(res, arithmetic_token_init(TOKEN_EOF, 0));
    return res;
}

void arithmetic_lexer_free(struct arithmetic_lexer *lexer)
{
    free(lexer);
}

struct arithmetic_token *arithmetic_lexer_peek(struct arithmetic_lexer *lexer)
{
    return lexer->head->token;
}

struct arithmetic_token *arithmetic_lexer_pop(struct arithmetic_lexer *lexer)
{
    if (!lexer->head)
    {
        return NULL;
    }
    struct arithmetic_token_list *head = lexer->head;
    lexer->head = lexer->head->next;
    lexer->size--;
    struct arithmetic_token *tok = head->token;
    free(head);
    return tok;
}
