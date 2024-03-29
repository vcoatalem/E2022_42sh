#include "../parser.h"

static enum operator_type rule_id_to_operator3(enum rule_id id)
{
    if (id == RULE_FUNCDEC)
        return OPERATOR_FUNC_DECLARATION;
    if (id == RULE_VARDEC)
        return OPERATOR_VAR_DECLARATION;
    if (id == RULE_DO_GROUP)
        return OPERATOR_DO;
    if (id == RULE_COMMAND_NOT)
        return OPERATOR_NOT;
    if (id == RULE_CASE
        || id == RULE_CASE_CLAUSE
        || id == RULE_CASE_LINEBREAK
        || id == RULE_CASE_CLAUSE_CONCAT
        || id == RULE_CASE_DELIM
        || id == RULE_CASE_ITEM_CONCAT)
        return OPERATOR_CASE;
    if (id == RULE_FOR
        || id == RULE_FOR_LINEBREAK
        || id == RULE_FOR_DELIM)
        return OPERATOR_FOR;
    if (id == RULE_IF)
        return OPERATOR_IF;
    if (id == RULE_THEN)
        return OPERATOR_THEN;
    if (id == RULE_WHILE)
        return OPERATOR_WHILE;
    return OPERATOR_NONE;
}

static enum operator_type rule_id_to_operator2(enum rule_id id)
{
    if (id == RULE_UNTIL)
        return OPERATOR_UNTIL;
    if (id == RULE_ELSE_CONCAT)
        return OPERATOR_ELSE;
    if (id == RULE_ARG_LIST || id == RULE_ELEMENT_LIST
        || id == RULE_ELEMENT_ANY_LIST || id == RULE_FOR_ELEMENT_LIST
        || id == RULE_FOR_CLAUSE)
        return OPERATOR_ARG_LIST;
    if (id == RULE_REDIR)
        return OPERATOR_REDIR;
    if (id == RULE_REDIR_LIST)
        return OPERATOR_REDIR_LIST;
    if (id == RULE_ELEMENT || id == RULE_ELEMENT_ANY || id == RULE_CASE_ITEM)
        return OPERATOR_GET_VALUE;
    if (id == RULE_ELEMENT_EXPAND)
        return OPERATOR_GET_EXPAND_VALUE;
    if (id == RULE_ELEMENT_SUBSHELL)
        return OPERATOR_GET_SUBSHELL_VALUE;
    if (id == RULE_ELEMENT_ARITHMETIC)
        return OPERATOR_GET_ARITHMETIC_VALUE;
    if (id == RULE_ELEMENT_TILDE)
        return OPERATOR_GET_TILDE_VALUE;
    if (id == RULE_ELEMENT_NO_SUBSTITUTION)
        return OPERATOR_GET_NO_SUBSTITUTION_VALUE;
    if (id == RULE_REDIR_SYMBOL)
        return OPERATOR_GET_REDIR_SYMBOL;
    if (id == RULE_IONUMBER)
        return OPERATOR_GET_IONUMBER;
    if (id == RULE_REDIR_TO)
        return OPERATOR_GET_REDIR_TO;
    return rule_id_to_operator3(id);
}

enum operator_type rule_id_to_operator(enum rule_id id)
{
    if (id == RULE_INPUT || id == RULE_LIST_DELIM
        || id == RULE_LIST || id == RULE_LIST_DELIM
        || id == RULE_LIST_CONCAT || id == RULE_COMPOUND_LIST_BREAK
        || id == RULE_COMPOUND_LIST_BREAK_DELIM
        || id == RULE_COMPOUND_LIST_BREAK_CONCAT
        || id == RULE_COMPOUND_LIST_BREAK_LINE
        || id == RULE_COMPOUND_LIST || id == RULE_COMPOUND_LIST_CONCAT
        || id == RULE_COMPOUND_LIST_DELIM || id == RULE_COMPOUND_LIST_NEXT
        || id == RULE_FUNCDEC_BODY)
    {
        return OPERATOR_LIST;
    }
    if (id == RULE_AND_CONCAT
        || id == RULE_AND_LINEBREAK
        || id == RULE_AND_OR)
    {
        return OPERATOR_AND;
    }
    if (id == RULE_OR_CONCAT
        || id == RULE_OR_LINEBREAK
        || id == RULE_OR)
    {
        return OPERATOR_OR;
    }
    if (id == RULE_PIPELINE
        || id == RULE_PIPE)
    {
        return OPERATOR_PIPE;
    }
    if (id == RULE_COMMAND
        || id == RULE_SIMPLE_COMMAND)
    {
        return OPERATOR_COMMAND;
    }
    if (id == RULE_SHELL_COMMAND)
        return OPERATOR_SHELL_COMMAND;
    return rule_id_to_operator2(id);
}
