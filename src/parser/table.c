#include "parser.h"

struct analysis_table *table_init(void)
{
    struct analysis_table *t = calloc(1, sizeof(struct analysis_table));

    struct rule_array *rules = rule_array_build();
    t->n_rules = NB_RULES;
    t->n_symbols = NB_TOKENS + 1; //SYMBOLE_END 
    printf("---NEXT() values:\n");
    for (size_t i = 1; i < NB_RULES; i++)
    {
        printf("[RULE#%zu] ", i);
        struct symbol_array *nexts = next(i, rules);
        symbol_array_print(nexts);
        printf("\n");
    }
    printf("--------------------------------------\n\n\n");
    //build table
    struct symbol_array ***transformation_mat = calloc(t->n_rules,
        sizeof(void*));
    for (size_t i = 0; i < t->n_rules; i++)
    {
        struct symbol_array **line = calloc(t->n_symbols, sizeof(void*));
        *(transformation_mat + i) = line;
    }

    //Pour toute règle de la forme X->alpha 
    for (size_t i = 0; i < rules->size; i++)
    {
        struct rule *rule = *(rules->rules + i);
        struct symbol_array **line = transformation_mat[rule->rule_id];
        
        struct symbol_array *firsts = first(rule->symbols, rules);
        if (firsts)
        {
            //Pour tout a dans Premier(alpha)
            for (size_t j = 0; j < firsts->size; j++)
            {
                //Ajouter X->alpha à la case d'indice (a,X)
                struct symbol *a = firsts->array[j];
                line[a->token_type] = symbol_array_dup(rule->symbols);
            }
            symbol_array_free(firsts);
        //Fin Pour
        }
        //Si Eps(alpha) vaut vrai Alors
        if (expr_is_epsilon(rule->symbols))
        {
            struct symbol_array *nexts = next(rule->rule_id, rules);
            if (nexts)
            {
                //Pour tout b dans suivant(alpha)
                for (size_t j = 0; j < nexts->size; j++)
                {
                    struct symbol *b = nexts->array[j];
                    size_t index = b->type == SYMBOL_TOKEN ? b->token_type
                        : t->n_symbols - 1;
                    //Ajouter X->alpha à la case d'indice (b,X)
                    if (!line[index])
                    {
                        //some nexts will be duplicated
                        line[index] = symbol_array_dup(rule->symbols);
                    }
                }
                symbol_array_free(nexts);
            }
            //Fin Pour
        }
        //Fin Pour
    }
    t->transformation_mat = transformation_mat;
    rule_array_free(rules);
    //Fin Pour
    return t;
}

void table_print(struct analysis_table *table)
{
    for (size_t i = 0; i < table->n_rules; i++)
    {
        struct symbol_array **line = table->transformation_mat[i];
        int count = 0;
        printf("rule #%zu:", i);
        for (size_t j = 0; j < table->n_symbols; j++)
        {
            if (line[j])
            {
                printf("[ `%s`: ", j < table->n_symbols - 1 ?
                        token_to_string(j) : "$");
                symbol_array_print(line[j]);
                printf(" ]");
                count++;
            }
        }
        if (count == 0)
        {
            printf("table empty");
        }
        printf("\n");
    }
}

void table_free(struct analysis_table *table)
{
    for (size_t i = 0; i < NB_RULES; i++)
    {
        struct symbol_array **line = *(table->transformation_mat + i);
        for (size_t j = 0; j < NB_TOKENS; j++)
        {
            if (line[j])
            {
                symbol_array_free(line[j]);
            }
        }
        free(line);
    }
    free(table->transformation_mat);
    free(table);
}
