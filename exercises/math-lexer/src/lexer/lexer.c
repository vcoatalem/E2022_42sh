#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

#include "lexer.h"
#include "token_list.h"

struct token *token_init(enum token_type type, int value)
{
    struct token *res = malloc(sizeof(struct token));
    if (!res)
        return NULL;
    res->type = type;
    res->value = value;
    return res;
}

struct token_list *token_list_init(struct token *token)
{
    struct token_list *tok_list = malloc(sizeof(struct token_list));
    if (!tok_list)
    {
        return NULL;
    }
    tok_list->token = token;
    tok_list->next = NULL;
    return tok_list;
}

enum token_type get_type(char c)
{
    enum token_type type;
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
        type = TOKEN_LEFT_PARENTHESIS;
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

void token_list_appen(struct lexer *lexer,  struct token *tok)
{
    struct token_list *res = token_list_init(tok);
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

struct lexer *lexer_alloc(const char *str)
{
    struct lexer *res = calloc(1, sizeof(struct lexer));
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
        enum token_type type = get_type(c);
        if (type != TOKEN_NUMBER || c == ' ')
        {
            if (index != 0)
            {
                buff[index] = '\0';
                int val = atoi(buff);
                index = 0;
                struct token *tok = token_init(TOKEN_NUMBER, val);
                token_list_appen(res, tok);
            }
            if (c != ' ')
            {
                struct token *tok = token_init(type, 0);
                token_list_appen(res, tok);
            }
        }
        else
        {
            buff[index] = c;
            index++;
        }
    }
    buff[index] = '\0';
    int val = atoi(buff);
    index = 0;
    struct token *tok = token_init(TOKEN_NUMBER, val);
    token_list_appen(res, tok);
    token_list_appen(res, token_init(TOKEN_EOF, 0));
    return res;
}

void lexer_free(struct lexer *lexer)
{
    free(lexer);
}

struct token *lexer_peek(struct lexer *lexer)
{
    return lexer->head->token;
}

struct token *lexer_pop(struct lexer *lexer)
{
    if (!lexer->head)
    {
        return NULL;
    }
    struct token_list *head = lexer->head;
    lexer->head = lexer->head->next;
    lexer->size--;
    struct token *tok = head->token;
    free(head);
    return tok;
}
