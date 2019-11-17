#include "../parser.h"

int main()
{
    struct analysis_table *table = table_init();
    table_print(table);
    table_free(table);
    return 0;
}
