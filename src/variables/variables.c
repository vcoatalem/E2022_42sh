#include <stdio.h>
#include <string.h>
#include <err.h>
#include "variables.h"

int is_delimiter(char c)
{
    return (c == ' ' || c == '\t' || c == '|' || c == '&' || c == '\n'
         || c == '(' || c == ')' || c == '\0' || c == '<' || c == '>'
         || c == ';' || c == '$');
}


char *getword(char *word, struct hash_table_var *ht)
{
    //printf("word=%s\n", word);
    if (word[0] != '$' || strlen(word) == 1)
        return word;
    if (word[1] == '{' && word[strlen(word) - 1] == '}')
    {
        char *result = calloc(1, sizeof(word));
        for (size_t i = 0; i < strlen(word) - 3; ++i)
        {
            result[i] = word[i + 2];
        }
        char *value = get_variable(ht, result);
        free(result);
        return value;
    }
    if (word[1] != '{' && word[strlen(word) - 1] != '}')
    {
        char *result = calloc(1, sizeof(word));
        for (size_t i = 0; i < strlen(word) - 1; ++i)
        {
            result[i] = word[i + 1];
        }
        char *value = get_variable(ht, result);
        free(result);
        return value;
    }
    warn("bad formulation of variable: %s", word);
    return NULL;

}

char *recvar_substitute(char* text, struct hash_table_var *ht,
    int *did_substitute)
{
    //printf("text=%s\n", text);
    char *word = calloc(1, strlen(text) * sizeof(char));
    //word = strdup(text);
    int i = 0;
    for (; text[i] && text[i] != '$'
        || (text[i] == '$' && is_delimiter(text[i + 1])); ++i)
    {
    }
    int iword = i;
    for (int j = 0; !is_delimiter(text[i + 1]) && text[i] != '}'; ++j, ++i)
        word[j] = text[i];
    word[strlen(word)] = text[i];
    char *value = getword(word, ht);
    int lenword = strlen(word);
    int dec = lenword - strlen(value);
    free(word);
    char *result = calloc(1, (strlen(text) + strlen(value)) * sizeof(char));
    strcpy(result, text);
    if(strcmp(value, "") == 0)
    {
        for (int i = iword; i < strlen(result); ++i)
        {
            result[i] = result[i + lenword];
        }
    }
    else if (dec < 0)
    {
        for (int i = strlen(result) - dec; i >= iword; --i)
            result[i] = result[i + dec];
    }
    else
    {
        for (size_t i = iword + dec; i < strlen(result); i++)
        {
            result[i] = result[i + dec];
        }
    }
    if (lenword >= 1)
    {
        for (size_t j = 0; j < strlen(value); ++j)
        {
            result[iword] = value[j];
            iword++;
        }
    }
    if (i >= strlen(text) - 1)
    {
        *did_substitute = 0;
    }
    return result;
}

char *var_substitute(char *text, struct hash_table_var *ht)
{
    int did_substitute = 1;
    char *newstr = recvar_substitute(text, ht, &did_substitute);
    char *newnewstr;
    if (did_substitute)
    {
        newnewstr = var_substitute(newstr, ht);
        free(newstr);
    }
    if (did_substitute)
        return newnewstr;
    return newstr;
}
/*
int main(void)
{
    struct hash_table_var *ht = init_hash_table_var(50);
    insert_variable(ht, "lol", "baba");
    char *line = " $ $lol$HOME non$klzea";
    char *test = var_substitute(line, ht);
    printf("%s\n", test);
    free(test);
    free_hash_table_var(ht);
}
*/
