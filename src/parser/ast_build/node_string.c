#include "../parser.h"

char *rule_id_to_string(enum rule_id id)
{
    switch (id)
    {
    case RULE_NONE:
        return "none";
    case RULE_INPUT:
        return "input";
    case RULE_LIST_DELIM:
        return "list_delim";
    case RULE_LIST_CONCAT:
        return "list_concat";
    case RULE_LIST:
        return "list";
    case RULE_COMPOUND_LIST_LINEBREAK:
        return "compound_list_linebreak";
    case RULE_COMPOUND_LIST_DELIM:
        return "list_delim";
    case RULE_COMPOUND_LIST_CONCAT:
        return "list_concat";
    case RULE_COMPOUND_LIST:
        return "list";
    case RULE_AND_OR:
        return "and|or";
    case RULE_AND_CONCAT:
        return "and_concat";
    case RULE_AND_LINEBREAK:
        return "and_linebreak";
    case RULE_OR_CONCAT:
        return "or_concat";
    case RULE_OR_LINEBREAK:
        return "or_linebreak";
    case RULE_PIPELINE:
        return "|";
    case RULE_PIPE:
        return "|";
    case RULE_COMMAND:
        return "command";
    case RULE_SIMPLE_COMMAND:
        return "simple_command";
    case RULE_SHELL_COMMAND:
        return "shell_command";
    case RULE_REDIR:
        return "redirection";
    case RULE_REDIR_TO:
        return "redirection_to";
    case RULE_REDIR_SYMBOL:
        return "redirection_symbol";
    case RULE_REDIR_LIST:
        return "redirection_list";
    case RULE_IONUMBER:
        return "ionumber";
    case RULE_ELEMENT:
        return "element";
    case RULE_ELEMENT_LIST:
        return "element list";
    case RULE_ARG_LIST:
        return "args";
    case RULE_IF:
        return "if";
    case RULE_ELSE_CONCAT:
        return "else";
    default:
        return "unknown";
    }
}
