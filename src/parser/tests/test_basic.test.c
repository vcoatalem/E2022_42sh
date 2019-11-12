#include "../parser.h"

int main()
{
    union value t = { .sub_test = NULL, .token = NULL, .rule_id = RULE_NONE };
    struct test *test = test_init(TEST_RULE, t, 1, 0);
}
