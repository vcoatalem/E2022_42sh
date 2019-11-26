#include "../parser.h"

static enum operator_type rule_id_to_operator2(enum rule_id id)
{
    if (id == RULE_UNTIL)
        return OPERATOR_UNTIL;
    if (id == RULE_ELSE_CONCAT)
        return OPERATOR_ELSE;
    if (id == RULE_ARG_LIST || id == RULE_ELEMENT_LIST
            || id == RULE_ELEMENT_ANY_LIST)
        return OPERATOR_ARG_LIST;
    if (id == RULE_REDIR)
        return OPERATOR_REDIR;
    if (id == RULE_REDIR_LIST)
        return OPERATOR_REDIR_LIST;
    if (id == RULE_ELEMENT || id == RULE_ELEMENT_ANY)
        return OPERATOR_GET_VALUE;
    if (id == RULE_REDIR_SYMBOL)
        return OPERATOR_GET_REDIR_SYMBOL;
    if (id == RULE_IONUMBER)
        return OPERATOR_GET_IONUMBER;
    if (id == RULE_REDIR_TO)
        return OPERATOR_GET_REDIR_TO;
    if (id == RULE_FUNCDEC)
        return OPERATOR_FUNC_DECLARATION;
    if (id == RULE_VARDEC)
        return OPERATOR_VAR_DECLARATION;
    if (id == RULE_DO_GROUP)
        return OPERATOR_DO;
    return OPERATOR_NONE;
}

enum operator_type rule_id_to_operator(enum rule_id id)
{
    if (id == RULE_INPUT || id == RULE_LIST_DELIM
        || id == RULE_LIST || id == RULE_LIST_DELIM || id == RULE_LIST_CONCAT
        || id == RULE_COMPOUND_LIST_BREAK || id == RULE_COMPOUND_LIST_BREAK_DELIM || id == RULE_COMPOUND_LIST_BREAK_CONCAT || id == RULE_COMPOUND_LIST_BREAK_LINE
        || id == RULE_COMPOUND_LIST || id == RULE_COMPOUND_LIST_CONCAT || id == RULE_COMPOUND_LIST_DELIM || id == RULE_COMPOUND_LIST_NEXT
        || id == RULE_FUNCDEC_BODY)
    {
        return OPERATOR_LIST;
    }
    if (id == RULE_AND_CONCAT || id == RULE_AND_LINEBREAK
        || id == RULE_AND_OR)
        return OPERATOR_AND;
    if (id == RULE_OR_CONCAT || id == RULE_OR_LINEBREAK || id == RULE_OR)
        return OPERATOR_OR;
    if (id == RULE_PIPELINE || id == RULE_PIPE)
        return OPERATOR_PIPE;
    if (id == RULE_COMMAND || id == RULE_SIMPLE_COMMAND)
        return OPERATOR_COMMAND;
    if (id == RULE_SHELL_COMMAND)
        return OPERATOR_SHELL_COMMAND;
    if (id == RULE_IF)
        return OPERATOR_IF;
    if (id == RULE_THEN)
        return OPERATOR_THEN;
    if (id == RULE_WHILE)
        return OPERATOR_WHILE;
    return rule_id_to_operator2(id);
}
