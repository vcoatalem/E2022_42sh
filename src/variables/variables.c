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
    return "";

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
    
    //printf("text=%s\n", text);
    //printf("i=%d\n", i);
    //printf("c=%c\n", text[i]);
    word[strlen(word)] = text[i];

    //word = realloc(word, 8 * strlen(word));
    //printf("word2=%s\n", word);
    char *value = getword(word, ht);
    //printf("val=%s\n",value);
    int lenword = strlen(word);
    int dec = lenword - strlen(value);
    free(word);
    char *result = calloc(1, (strlen(text) + strlen(value)) * sizeof(char));
    strcpy(result, text);
    //printf("dec = %d\n", dec);
    if(strcmp(value, "") == 0)
    {
        //printf("resssbeaf=%s\n", result);
        for (int i = iword; i < strlen(result); ++i)
        {
            //printf("x\n");
            result[i] = result[i + lenword];
        }
        //printf("resssaft=%s\n", result);
    }
    else if(dec < 0)
        for (int i = strlen(result) - dec; i >= iword; --i)
            result[i] = result[i + dec];
    else
        for (size_t i = iword + dec; i < strlen(result); i++)
        {
            result[i] = result[i + dec];
        }
    //printf("resss=%s\n", result);
    if(dec != 0)
        for (size_t j = 0; j < strlen(value); ++j)
        {
            result[iword] = value[j];
            iword++;
        }
    //printf("iword=%d\n", iword);
    if (i >= strlen(text) - 1)
    {
        *did_substitute = 0;
    }
    return result;
}
/*
char *var_substitute(char* text, struct hash_table_var *ht)
{
    int did_substitute = 1;
    char *res = recvar_substitute(text, ht, &did_substitute);
    printf("res= %s\n", res);
    //char *res2 = recvar_substitute(res, ht);
    //printf("res2%s\n", res2);
    //char *res2 = recvar_substitute(res, ht);
    char *res2;
    for (size_t i = 0; i < strlen(res) - 1; ++i)
    {
        res2 = strdup(res);
        if (res[i] == '$' && !is_delimiter(res[i + 1]))
        {
            free(res);
            res = strdup(recvar_substitute(res2, ht, &did_substitute));
            i = 0;
        }
        free(res2);
    }
    return res;
}
*/
char *var_substitute(char* text, struct hash_table_var *ht)
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

int main(void)
{
    struct hash_table_var *ht = init_hash_table_var(50);
    char *line = "$lol$HOME non$klzea";
    char *test = var_substitute(line, ht);
    printf("%s\n", test);
    free(test);
    free_hash_table_var(ht);
}