#include "../parser.h"

enum operator_type rule_id_to_operator(enum rule_id id)
{
    if (id == RULE_INPUT || id == RULE_LIST_DELIM
        || id == RULE_LIST || id == RULE_COMPOUND_LIST_BREAK
        || id == RULE_LIST_DELIM || id == RULE_COMPOUND_LIST_BREAK_DELIM
        || id == RULE_LIST_CONCAT || id == RULE_COMPOUND_LIST_BREAK_CONCAT
        || id == RULE_LIST_DELIM || id == RULE_LIST_CONCAT
        || id == RULE_AND_OR || id == RULE_AND_OR_CONCAT
        || id == RULE_AND_CONCAT || id == RULE_AND_LINEBREAK
        || id == RULE_OR_CONCAT || id == RULE_OR_LINEBREAK
        || id == RULE_OR_CONCAT || id == RULE_DO_GROUP
        || id == RULE_FUNCDEC_BODY)
    {
        return OPERATOR_AND;
    }
    if (id == RULE_OR_CONCAT || id == RULE_OR_LINEBREAK)
    {
        return OPERATOR_NONE;
    }
    if (id == RULE_PIPELINE || id == RULE_PIPE)
    {
        return OPERATOR_PIPE;
    }
    if (id == RULE_COMMAND || id == RULE_SIMPLE_COMMAND
            || id == RULE_SHELL_COMMAND)
    {
        return OPERATOR_COMMAND;
    }
    if (id == RULE_IF)
    {
        return OPERATOR_IF;
    }
    if (id == RULE_ARG_LIST)
    {
        return OPERATOR_ARG_LIST;
    }
    if (id == RULE_REDIR)
    {
        return OPERATOR_REDIR;
    }
    if (id == RULE_REDIR_LIST)
    {
        return OPERATOR_REDIR_LIST;
    }
    if (id == RULE_ELEMENT || id == RULE_REDIR_SYMBOL)
    {
        return OPERATOR_GET_VALUE;
    }
    if (id == RULE_FUNCDEC)
    {
        return OPERATOR_FUNC_DECLARATION;
    }
    return OPERATOR_NONE;
}
