#include "parser.h"

static int g_n_conflicts = 0;

static void log_conflict(struct rule *rule, size_t index,
        struct symbol_array *in_slot, struct symbol_array *to_be_inserted)
{
      printf("[LL PARSER] got conflict for rule: ");
      rule_print(rule);
      printf("\n");
      printf("[LL PARSER] in slot `");
      if (index == NB_TOKENS)
      {
        printf("$");
      }
      else
      {
        printf("%s", token_to_formatted_string(index));    
      }
      printf("` ; ");
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
    if (firsts->size > 0)
    {
        for (size_t j = 0; j < firsts->size; j++)
        {
            struct symbol *a = firsts->array[j];
            size_t index = a->token_type;
            if (line[index] && expr_is_epsilon(line[index]))
            {
                //if current slot has an epsilon, we have a conflict.
                //we opt to reduce always reduce (replace the epsilon expr
                //with the new one)
                log_conflict(rule, index, line[index], rule->symbols);
                symbol_array_free(line[index]); 
                line[index] = symbol_array_dup(rule->symbols);
            }
            else if (!line[index])
            {
                line[index] = symbol_array_dup(rule->symbols);
            }
            else
            {
                if (!symbol_array_equal(line[index], rule->symbols))
                {
                    log_conflict(rule, index, line[index], rule->symbols);
                }
            }
        }
    }
    else if (expr_is_epsilon(rule->symbols))
    {
        struct symbol_array *nexts = rule_next(rule->rule_id, rules, NULL);
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
                        log_conflict(rule, index, line[index], rule->symbols);
                    }
                }
            }
            symbol_array_free(nexts);
        }
    }
    symbol_array_free(firsts);
}

static struct analysis_table *table_init(void)
{
    struct analysis_table *t = calloc(1, sizeof(struct analysis_table));
    struct rule_array *ll_rules = rule_array_build();
    t->rules = ll_rules;
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
    return t;
}

struct analysis_table *table_build(void)
{
    struct analysis_table *t = table_init();
    for (size_t i = 0; i < t->rules->size; i++)
    {
        struct rule *rule = t->rules->rules[i];
        #if 0
        printf("[LL PARSER] ---------- [TABLE] setting rule #%zu ; ", i);
        rule_print(rule);
        printf("\n");
        #endif
        fill_line_slot(t, rule, t->rules);
    }
    rule_array_free(t->rules);
    printf("[LL PARSER] Built analysis table." );
    printf("[LL PARSER] Found #%d conflicts in grammar\n", g_n_conflicts);
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
                        token_to_formatted_string(j) : "$");
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
