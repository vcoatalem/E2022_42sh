#include "parser.h"

struct rule *rule_build(enum rule_id id, struct symbol *s, ...)
{
    va_list symbols;
    va_start(symbols, s);
    struct symbol_array *array = symbol_array_init();
    while (s)
    {
        symbol_array_add(array, s);
        s = va_arg(symbols, struct symbol*);
    }
    va_end(symbols);
    struct rule *res = calloc(1, sizeof(struct rule));
    res->symbols = array;
    res->rule_id = id;
    return res;
}

void rule_print(struct rule *rule)
{
    printf("ID: %d ; EXPRESSION:  ", rule->rule_id);
    symbol_array_print(rule->symbols);
}

void rule_free(struct rule *rule)
{
    symbol_array_free(rule->symbols);
    free(rule);
}
