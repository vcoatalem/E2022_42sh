#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

#include "lexer.h"
#include "token_list.h"
#include "../../main/42sh.h"

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

void arithmetic_lexer_print(struct arithmetic_lexer *lexer)
{
    struct arithmetic_token_list *it = lexer->head;
    while (it)
    {
        printf("-> [t: %d, v: %d]", it->token->type, it->token->value);
        it = it->next;
    }
    printf("\n");
}


static enum arithmetic_token_type get_type2(char *buffer)
{
    if (!strcmp(buffer, "^"))
        return A_TOKEN_BITWISE_XOR;
    else if (!strcmp(buffer, "&&"))
        return A_TOKEN_AND;
    else if (!strcmp(buffer, "||"))
        return A_TOKEN_OR;
    else if (!strcmp(buffer, "**"))
        return A_TOKEN_POWER_N; 
    else if (!strcmp(buffer, "!"))
        return A_TOKEN_NOT;
    else if (!strcmp(buffer, "~"))
        return A_TOKEN_INVERT;
    else if (!strcmp(buffer, "/"))
        return A_TOKEN_DIVIDE;
    else if (!strcmp(buffer, "("))
        return A_TOKEN_LEFT_PARENTHESIS;
    else if (!strcmp(buffer, ")"))
        return A_TOKEN_RIGHT_PARENTHESIS;
    else if (!strcmp(buffer, ""))
        return A_TOKEN_EOF;
    return A_TOKEN_NUMBER;
}

static enum arithmetic_token_type get_type(char *buffer, const char *str,
        size_t *iterator)
{
    if (!strcmp(buffer, "+"))
        return A_TOKEN_PLUS;
    else if (!strcmp(buffer, "-"))
        return A_TOKEN_MINUS;
    else if (!strcmp(buffer, "*"))
    {
        if (*(str + *iterator + 1) == '*')
        {
            *iterator = *iterator + 1;
            return A_TOKEN_POWER_N;
        }
        return A_TOKEN_MULTIPLY;
    }
    else if (!strcmp(buffer, "&"))
    {
        if (*(str + *iterator + 1) == '&')
        {
            *iterator = *iterator + 1;
            return A_TOKEN_AND;
        }
        return A_TOKEN_BITWISE_AND;
    }
    else if (!strcmp(buffer, "|"))
    {
        if (*(str + *iterator + 1) == '|')
        {
            *iterator = *iterator + 1;
            return A_TOKEN_OR;
        }
        return A_TOKEN_BITWISE_OR;
    }
    return get_type2(buffer);
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
        struct arithmetic_lexer *lexer, void *bundle_ptr)
{
    struct execution_bundle *bundle = bundle_ptr;
    if (*index == 0)
        return;
    buff[*index] = '\0';
    int val = atoi(buff);
    if (val == 0 && strcmp(buff, "0"))
    {
        //buffer contans alphanumerical char -> finds associated variable
        char *variable = get_variable(bundle->hash_table_var, buff);
        if (strcmp(variable, ""))
        {
            val = atoi(variable);
        }
    }
    *index = 0;
    struct arithmetic_token *tok = arithmetic_token_init(A_TOKEN_NUMBER, val);
    arithmetic_token_list_append(lexer, tok);
}

struct arithmetic_lexer *arithmetic_lexer_alloc(const char *str,
        void *bundle_ptr)
{
    struct arithmetic_lexer *res = calloc(1, sizeof(struct arithmetic_lexer));
    if (!res)
    {
        return NULL;
    }
    // transform *str to a char token
    char buff[1024] = { 0 };
    char op_buff[1024] = { 0 };
    size_t op_index = 0;
    size_t index = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        if (c != ' ' && (c < '0' || c > '9'))
        {
            op_buff[op_index] = c;
            op_buff[op_index + 1] = 0;
            op_index++;
        }
        enum arithmetic_token_type type = get_type(op_buff, str, &i);
        if ((type != A_TOKEN_EOF && type != A_TOKEN_NUMBER) || c == ' ')
        {
            op_index = 0;
            op_buff[op_index] = 0;
            add_number_token(buff, &index, res, bundle_ptr);
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
    add_number_token(buff, &index, res, bundle_ptr);
    arithmetic_token_list_append(res, arithmetic_token_init(A_TOKEN_EOF, 0));
    return res;
}

void arithmetic_lexer_free(struct arithmetic_lexer *lexer)
{
    struct arithmetic_token_list *it = lexer->head;
    while (it)
    {
        struct arithmetic_token_list *next_it = it->next;
        free(it->token);
        free(it);
        it = next_it;
    }
    free(lexer);
}

struct arithmetic_token *arithmetic_lexer_peek(struct arithmetic_lexer *lexer)
{
    return lexer->head ? lexer->head->token : NULL;
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
