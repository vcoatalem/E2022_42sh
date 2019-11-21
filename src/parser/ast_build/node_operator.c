#include "../parser.h"

enum operator_type rule_id_to_operator(enum rule_id id)
{
    switch (id)
    {
    case RULE_NONE:
        return OPERATOR_NONE;
    case RULE_INPUT:
        return OPERATOR_AND;
    case RULE_LIST:
        return OPERATOR_AND;
    case RULE_LIST_DELIM:
        return OPERATOR_NONE;
    case RULE_LIST_CONCAT:
        return OPERATOR_AND;
    case RULE_LIST_END:
        return OPERATOR_NONE;
    case RULE_COMPOUND_LIST:
        return OPERATOR_AND;
    case RULE_COMPOUND_LIST_CONCAT:
        return OPERATOR_AND;
    case RULE_COMPOUND_LIST_END:
        return OPERATOR_NONE;
    case RULE_COMPOUND_LIST_LINEBREAK:
        return OPERATOR_AND;
    case RULE_AND_OR:
        return OPERATOR_AND;
    case RULE_AND_OR_CONCAT:
        return OPERATOR_AND;
    case RULE_AND_CONCAT:
        return OPERATOR_AND;
    case RULE_AND_LINEBREAK:
        return OPERATOR_AND;
    case RULE_OR_CONCAT:
        return OPERATOR_OR;
    case RULE_OR_LINEBREAK:
        return OPERATOR_OR;
    case RULE_PIPELINE:
        return OPERATOR_PIPE;
    case RULE_PIPE:
        return OPERATOR_PIPE;
    case RULE_SHELL_COMMAND:
        return OPERATOR_NONE;
    case RULE_SIMPLE_COMMAND:
        return OPERATOR_NONE;
    case RULE_COMMAND:
        return OPERATOR_NONE;
    case RULE_REDIR_LIST:
        return OPERATOR_NONE;
    case RULE_REDIR:
        return OPERATOR_NONE;
    case RULE_REDIR_SYMBOL:
        return OPERATOR_NONE;
    case RULE_REDIR_TO:
        return OPERATOR_NONE;
    case RULE_IONUMBER:
        return OPERATOR_NONE;
    case RULE_ELEMENT:
        return OPERATOR_NONE;
    case RULE_ELEMENT_LIST:
        return OPERATOR_NONE;
    case RULE_ARG_LIST:
        return OPERATOR_NONE;
    case RULE_IF:
        return OPERATOR_NONE;
    case RULE_ELSE_CONCAT:
        return OPERATOR_NONE;
    default:
        return OPERATOR_NONE;
    }
}
