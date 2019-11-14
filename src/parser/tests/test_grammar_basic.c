#include "../parser.h"

int main(int argc, char **argv)
{
    struct grammar *g = grammar_build();
    for (size_t i = 1; i < NB_RULES; i++)
    {
        rule_print(g->rules[i], stdout);
    }
}
