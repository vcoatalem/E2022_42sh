#include "parser.h"

static int g_n_conflicts = 0;

static void log_conflict(enum rule_id rule_id, struct symbol_array *in_slot,
        struct symbol_array *to_be_inserted)
{
    printf("array equal : %d\n", symbol_array_equal(in_slot, to_be_inserted));
      printf("[LL PARSER] got conflict for rule #%d:\n", rule_id);
      printf("[LL PARSER] in slot: ");
      symbol_array_print(in_slot);
      printf("\n");
      printf("[LL PARSER] to be inserted: ");
      symbol_array_print(to_be_inserted);
      printf("\n");
      g_n_conflicts++;
}

void fill_line_slot(struct analysis_table *t,
        struct rule *rule, struct rule_array *rules)
{   
    struct symbol_array **line = t->transformation_mat[rule->rule_id];
    struct symbol_array *firsts = expr_first(rule, rules);
    if (firsts)
    {
        for (size_t j = 0; j < firsts->size; j++)
        {
            struct symbol *a = firsts->array[j];
            if (!line[a->token_type])
            {
                line[a->token_type] = symbol_array_dup(rule->symbols);
            }
            else
            {
                if (!symbol_array_equal(line[a->token_type], rule->symbols))
                {
                    log_conflict(rule->rule_id, line[a->token_type],
                            rule->symbols);
                }
            }
        }
        symbol_array_free(firsts);
    }
    if (expr_is_epsilon(rule->symbols))
    {
        struct symbol_array *nexts = rule_next(rule->rule_id, rules);
        if (nexts)
        {
            for (size_t j = 0; j < nexts->size; j++)
            {
                struct symbol *b = nexts->array[j];
                size_t index = b->type == SYMBOL_TOKEN ? b->token_type
                    : t->n_symbols - 1;
                if (!line[index])
                {    
                    line[index] = symbol_array_dup(rule->symbols);
                }
                else
                {
                    if (!symbol_array_equal(line[index], rule->symbols))
                    {
                        log_conflict(rule->rule_id, line[index],
                                rule->symbols);
                    }
                }
            }
            symbol_array_free(nexts);
        }
    }
}

struct analysis_table *table_init(void)
{
    struct analysis_table *t = calloc(1, sizeof(struct analysis_table));

    struct rule_array *ll_rules = rule_array_build();
    t->n_rules = NB_RULES;
    t->n_symbols = NB_TOKENS + 1;
    struct symbol_array ***transformation_mat = calloc(t->n_rules,
        sizeof(void*));
    for (size_t i = 0; i < t->n_rules; i++)
    {
        struct symbol_array **line = calloc(t->n_symbols, sizeof(void*));
        *(transformation_mat + i) = line;
    }
    t->transformation_mat = transformation_mat;
    
    for (size_t i = 0; i < ll_rules->size; i++)
    {
        printf("---------- [TABLE] setting rule #%zu\n", i);
        struct rule *rule = ll_rules->rules[i];
        fill_line_slot(t, rule, ll_rules);
    }
    rule_array_free(ll_rules);
    printf("[LL PARSER] Built analysis table." );
    printf(" Found #%d conflicts in grammar\n", g_n_conflicts);
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
        for (size_t j = 0; j < table->n_symbols; j++)
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
