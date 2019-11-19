#include "../parser.h"

enum operator_type rule_id_to_operator(enum rule_id id)
{
    switch (id)
    {
    case RULE_NONE:
        return OPERATOR_NONE;
    case RULE_INPUT:
        return OPERATOR_AND;
    case RULE_AND_OR_CONCAT:
        return OPERATOR_AND;
    case RULE_AND_CONCAT:
        return OPERATOR_AND;
    case RULE_OR_CONCAT:
        return OPERATOR_OR;
    case RULE_AND_OR:
        return OPERATOR_AND;
    case RULE_PIPELINE:
        return OPERATOR_PIPE;
    case RULE_PIPE:
        return OPERATOR_PIPE;
    case RULE_COMMAND:
        return OPERATOR_NONE;
    case RULE_REDIR:
        return OPERATOR_NONE;
    case RULE_REDIR_SYMBOL:
        return OPERATOR_NONE;
    case RULE_REDIR_LIST:
        return OPERATOR_NONE;
    case RULE_IONUMBER:
        return OPERATOR_NONE;
    case RULE_ELEMENT:
        return OPERATOR_NONE;
    case RULE_ARG_LIST:
        return OPERATOR_NONE;
    default:
        return OPERATOR_NONE;
    }
}
