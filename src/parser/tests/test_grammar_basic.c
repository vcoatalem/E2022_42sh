#include "../parser.h"

int main()
{
    struct analysis_table *table = table_build();
    table_print(table);
    table_free(table);
    return 0;
}
