#include "parser.h"

struct analysis_table *table_init(void)
{
    struct analysis_table *t = calloc(1, sizeof(struct analysis_table));

    struct rule_array *rules = rule_array_build();
    t->n_rules = NB_RULES;
    t->n_symbols = NB_TOKENS;
   

    //build table
    struct symbol_array ***transformation_mat = calloc(NB_RULES,
        sizeof(void*));
    for (size_t i = 0; i < t->n_rules; i++)
    {
        struct symbol_array **line = calloc(NB_TOKENS, sizeof(void*));
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
        if (epsilon(rule->symbols))
        {
            struct symbol_array *nexts = next(rule->rule_id, rules);
            #if 0
            /**/printf("next for rule %d: ", rule->rule_id);
            /**/symbol_array_print(nexts);
            /**/printf("\n");
            #endif
            if (nexts)
            {
                //Pour tout b dans suivant(alpha)
                for (size_t j = 0; j < nexts->size; j++)
                {
                    struct symbol *b = nexts->array[j];
                    //Ajouter X->alpha à la case d'indice (b,X)
                    //Remplacer ?
                    if (!line[b->token_type])
                    {
                        line[b->token_type] = symbol_array_dup(rule->symbols);
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
    for (size_t i = 0; i < NB_RULES; i++)
    {
        struct symbol_array **line = table->transformation_mat[i];
        int count = 0;
        printf("rule #%zu:", i);
        for (size_t j = 0; j < NB_TOKENS; j++)
        {
            if (line[j])
            {
                printf("[ `%s`: ", token_to_string(j));
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
